#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

namespace http = boost::beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

int main() {
    try {
        // Setup the I/O context and acceptor
        asio::io_context io_context;

        // Create an endpoint for localhost on port 8080
        tcp::acceptor acceptor(io_context, { asio::ip::make_address("127.0.0.1"), 8080 });

        std::cout << "Server running on http://127.0.0.1:8080\n";

        while (true) {
            // Wait for an incoming connection
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            // Create a buffer to store the incoming request
            boost::beast::flat_buffer buffer;

            // Create a request object
            http::request<http::string_body> req;

            // Read the HTTP request
            http::read(socket, buffer, req);

            // Create the response
            http::response<http::string_body> res{ http::status::ok, req.version() };
            res.set(http::field::server, "C++ Server");
            res.set(http::field::content_type, "text/plain");
            res.content_length(13);  // "Hello, World!" is 13 characters long
            res.body() = "Hello, World!";

            // Send the response
            http::write(socket, res);

            // Close the socket
            socket.shutdown(tcp::socket::shutdown_send);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
