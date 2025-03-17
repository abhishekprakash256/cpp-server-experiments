#include <uWebSockets/App.h>
#include <iostream>

int main() {
    // Create a WebSocket server
    uWS::App().ws<nullptr>("/*", {
        .open = [](auto *ws) {
            std::cout << "Client connected!" << std::endl;
        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << "Received: " << message << std::endl;
            ws->send(message, opCode);  // Echo message back
        },
        .close = [](auto *ws, int code, std::string_view message) {
            std::cout << "Client disconnected!" << std::endl;
        }
    }).listen(9001, [](auto *listenSocket) {
        if (listenSocket) {
            std::cout << "WebSocket Server running on ws://localhost:9001" << std::endl;
        }
    }).run();

    return 0;
}
