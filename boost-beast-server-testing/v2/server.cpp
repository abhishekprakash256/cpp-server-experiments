/*
g++ -std=c++17 -o mac_server server.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_system -lboost_thread -pthread 


mkdir build && cd build
cmake ..
make


compile on both linux mac with using same commands with cmake

*/



#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

namespace beast = boost::beast;   // namespace used for the definition of variable , :: is used for the accessing the methods
namespace websocket = beast::websocket;   
namespace net = boost::asio;
using tcp = net::ip::tcp;



void do_session(tcp::socket socket) {
    try {
        websocket::stream<tcp::socket> ws{std::move(socket)};     // ws for socket,  
        ws.accept();

        for (;;) {  // infinte loop
            beast::flat_buffer buffer;   // temprory bufer to hold the value
            ws.read(buffer);   //wait for the mesaage to read
            std::string msg = beast::buffers_to_string(buffer.data());   // convert the raw data to string
            std::cout << "Received: " << msg << std::endl;  

            ws.text(ws.got_text());   //sends a message as text 
            ws.write(net::buffer("Echo: " + msg));   // sends the echo client
        }
    } catch (std::exception& e) {
        std::cerr << "Session error: " << e.what() << "\n";    
    }
}


int main() {
    try {
        net::io_context ioc;     //event loop for boost.asio
        tcp::acceptor acceptor{ioc, {tcp::v4(), 8080}}; // sets up the tcp acceptor litens on port 8080
        std::cout << "WebSocket server running on ws://localhost:8080\n";  

        while (true) {
            tcp::socket socket{ioc};  // creates a socket
            acceptor.accept(socket);  // accepts the socket
            std::thread{do_session, std::move(socket)}.detach(); 
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }
}