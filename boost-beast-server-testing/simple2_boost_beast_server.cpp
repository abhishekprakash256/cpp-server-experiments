/*

uinsg the link

- https://medium.com/@sidhanthpandey/how-to-create-an-http-server-in-c-812cee49ff77

compiling instructions -- 

g++ -std=c++17 -o mac_simple2_boost_beast_server simple2_boost_beast_server.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_system -lboost_thread -pthread         #for mac

g++ -o test_boost_beast_server test_boost_beast_server.cpp -lboost_system -lboost_thread -pthread         #for linux



*/



#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>


using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;



void handleRequest(http::request<http::string_body>& request, tcp::socket& socket) {
    // Prepare the response message
    http::response<http::string_body> response;
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::server, "My HTTP Server");
    response.set(http::field::content_type, "text/plain");
    response.body() = "Hello, World!";
    response.prepare_payload();

    // Send the response to the client
    boost::beast::http::write(socket, response);
}

void runServer() {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, {tcp::v4(), 8080});

    while (true) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);

        // Read the HTTP request
        boost::beast::flat_buffer buffer;
        http::request<http::string_body> request;
        boost::beast::http::read(socket, buffer, request);

        // Handle the request
        handleRequest(request, socket);

        // Close the socket
        socket.shutdown(tcp::socket::shutdown_send);
    }
}


int main() {
    try {
        runServer();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}