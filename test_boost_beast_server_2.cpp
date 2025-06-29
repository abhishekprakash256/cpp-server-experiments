/*
A test code for boost beast server using WebSocket.
*/

// server.cpp
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = net::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

// Handles an HTTP server connection
void do_session(tcp::socket socket)
{
    try
    {
        beast::flat_buffer buffer;

        // Read a request
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        // Create a response
        http::response<http::string_body> res{
            http::status::ok, req.version()};
        res.set(http::field::server, "Boost.Beast Server");
        res.set(http::field::content_type, "text/plain");
        res.body() = "Hello, world!";
        res.prepare_payload();

        // Write the response
        http::write(socket, res);

        // Gracefully close the socket
        beast::error_code ec;
        socket.shutdown(tcp::socket::shutdown_send, ec);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error in session: " << e.what() << "\n";
    }
}

int main()
{
    try
    {
        const auto address = net::ip::make_address("0.0.0.0");
        const unsigned short port = 8080;

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};

        std::cout << "Server listening on http://0.0.0.0:" << port << "\n";

        for(;;)
        {
            tcp::socket socket{ioc};

            acceptor.accept(socket);

            // Launch a thread to handle the session
            std::thread{std::bind(
                &do_session,
                std::move(socket))}.detach();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
// To compile this code, you need to link against Boost.Beast and Boost.Asio.
//g++ test_boost_beast_server_2.cpp -o test_boost_beast_server_2 -lpthread -lboost_system
