
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

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
    try {
        net::io_context ioc;
        tcp::resolver resolver{ioc};
        websocket::stream<tcp::socket> ws{ioc};

        auto const results = resolver.resolve("localhost", "8080");
        net::connect(ws.next_layer(), results);

        ws.handshake("localhost", "/");

        std::string msg = "Hello from client!";
        ws.write(net::buffer(msg));

        beast::flat_buffer buffer;
        ws.read(buffer);

        std::cout << "Received: " << beast::make_printable(buffer.data()) << "\n";
        ws.close(websocket::close_code::normal);

    } catch (std::exception& e) {
        std::cerr << "Client error: " << e.what() << "\n";
    }
}
