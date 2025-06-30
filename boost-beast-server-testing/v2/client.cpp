
/*
g++ -std=c++17 -o mac_client client.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_system -lboost_thread -pthread 


mkdir build && cd build
cmake ..
make

*/




#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

namespace beast = boost::beast;   // namespace used for the definition of variable , :: is used for the accessing the methods
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
    try {
        net::io_context ioc;   //event loop for boost.asio
        tcp::resolver resolver{ioc};   // Resolves hostnames like "localhost" and "8080" into an IP address and port.
        websocket::stream<tcp::socket> ws{ioc};   // Creates a WebSocket stream over a TCP socket.

        auto const results = resolver.resolve("localhost", "8080");   // Resolves "localhost:8080" into a list of endpoints (IP addresses).
        net::connect(ws.next_layer(), results);  // ws.next_layer() gives access to the underlying TCP socket inside the WebSocket stream.

        ws.handshake("localhost", "/");   // Performs the WebSocket handshake (i.e., upgrades the HTTP connection to a WebSocket connection)

        std::string msg = "Hello from client!";   // Prepares and sends a message to the server.
        ws.write(net::buffer(msg));   // wraps the string into a sendable buffer.

        beast::flat_buffer buffer;  // Allocates a buffer to receive a message.
        ws.read(buffer);  // Reads the server's response into that buffer (blocks until message is received).

        std::cout << "Received: " << beast::make_printable(buffer.data()) << "\n";  // Converts raw buffer data into a printable format.
        ws.close(websocket::close_code::normal);   // Closes the WebSocket connection gracefully.

    } catch (std::exception& e) {
        std::cerr << "Client error: " << e.what() << "\n";
    }
}
