/*
g++ -std=c++17 -o mac_server server.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_system -lboost_thread -pthread 


mkdir build && cd build
cmake ..
make

*/



#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void do_session(tcp::socket socket) {
    try {
        websocket::stream<tcp::socket> ws{std::move(socket)};
        ws.accept();

        for (;;) {
            beast::flat_buffer buffer;
            ws.read(buffer);
            std::string msg = beast::buffers_to_string(buffer.data());
            std::cout << "Received: " << msg << std::endl;

            ws.text(ws.got_text());
            ws.write(net::buffer("Echo: " + msg));
        }
    } catch (std::exception& e) {
        std::cerr << "Session error: " << e.what() << "\n";
    }
}

int main() {
    try {
        net::io_context ioc;
        tcp::acceptor acceptor{ioc, {tcp::v4(), 8080}};
        std::cout << "WebSocket server running on ws://localhost:8080\n";

        while (true) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread{do_session, std::move(socket)}.detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }
}
