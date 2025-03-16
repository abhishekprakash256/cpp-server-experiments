# C++ Server Experiments

This repository contains a series of experiments for building WebSocket servers in C++. The aim is to explore different aspects of C++ for real-time communication, server-side logic, and database integration.

## Overview

This project provides examples and learning resources for creating WebSocket servers in C++, integrating them with databases, and handling concurrent WebSocket connections. The goal is to learn and experiment with efficient communication systems using WebSockets and C++.

### Key Features:

- **WebSocket server setup**: Basic WebSocket server using `WebSocket++`.
- **Concurrency**: Handling multiple WebSocket connections simultaneously using threading.
- **Database integration**: Storing and retrieving messages using a database (e.g., MongoDB, MySQL).
- **Asynchronous I/O**: Using Boost.Asio for non-blocking I/O to improve server performance.

## Prerequisites

Before running the project, make sure you have the following installed:

- A C++11 or later compiler (e.g., `g++`).
- **CMake** for building the project.
- **WebSocket++**: A C++ library to handle WebSocket connections. Install it using your system's package manager or build from source.
- **Boost**: For asynchronous I/O handling (optional for certain experiments).

## How to Run

### 1. Clone the repository:

```bash
git clone https://github.com/abhishekprakash256/cpp-server-experiments.git
cd cpp-server-experiments
```

### 2. Build the project using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

### 3. Run the WebSocket server:

After building the project, you can start the WebSocket server by running:

```bash
./websocket_server
```

The server will listen for WebSocket connections on **port 9002** by default. You can modify the port in the source code if needed.

## Experiments

This project contains various experiments to help you understand WebSocket servers in C++:

1. **Basic WebSocket Server**: A simple WebSocket server that can accept connections and echo back messages to clients.
2. **Concurrency with Threading**: This experiment demonstrates how to manage multiple WebSocket connections concurrently using threads.
3. **WebSocket with Database**: Integrating the WebSocket server with a database to store and retrieve messages.
4. **Asynchronous I/O with Boost.Asio**: Using Boost's asynchronous I/O model to handle many connections efficiently.

## Database Integration

In the experiments that involve database integration, you will need to modify the code to connect to your desired database (e.g., MongoDB or MySQL). The database operations typically involve storing received messages or user data for retrieval.
