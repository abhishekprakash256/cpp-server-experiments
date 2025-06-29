# C++ Server Experiments

This repository contains a series of experiments for building WebSocket servers in C++. The aim is to explore different aspects of C++ for real-time communication, server-side logic, and database integration.

## Overview

This project provides examples and learning resources for creating WebSocket servers in C++, integrating them with databases, and handling concurrent WebSocket connections. The goal is to learn and experiment with efficient communication systems using WebSockets and C++.

### Key Features:

- **WebSocket server setup**: Basic WebSocket server using `boost beast`.
- **Concurrency**: Handling multiple WebSocket connections simultaneously using threading.
- **Database integration**: Storing and retrieving messages using a database (e.g., MongoDB, MySQL).
- **Asynchronous I/O**: Using Boost.Asio for non-blocking I/O to improve server performance.

## Prerequisites

Before running the project, make sure you have the following installed:


-- brew install boost, (for mac)
-- sudo apt-get install libboost-all-dev    (for linux)


## How to Run

### 1. Clone the repository:

```bash
git clone https://github.com/abhishekprakash256/cpp-server-experiments.git
cd cpp-server-experiments
```



### The compliling of the file are done seperately for OS 

- Linux file have linux_<file_name>
- Mac has file name as mac_<file_name>


### compiling is different for Mac and Linux 
- g++ -std=c++17 -o <file_name> <file_name>.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_system -lboost_thread -pthread                  # for mac 

- g++ -o test_boost_beast_server test_boost_beast_server.cpp -lboost_system -lboost_thread -pthread        #for Linux          




The server will listen for WebSocket connections on **port 8000** by default. You can modify the port in the source code if needed.

## Experiments

This project contains various experiments to help you understand WebSocket servers in C++:

1. **Bosst Beast**: A simple WebSocket server that can accept connections and echo back messages to clients.
2. **Concurrency with Threading**: This experiment demonstrates how to manage multiple WebSocket connections concurrently using threads.


## Database Integration

In the experiments that involve database integration, you will need to modify the code to connect to your desired database (e.g., MongoDB or MySQL). The database operations typically involve storing received messages or user data for retrieval.


Links -- 

```bash


https://www.scaledrone.com/websockets/c++

https://github.com/facundofarias/awesome-websockets?tab=readme-ov-file#c-1

https://www.boost.org/doc/libs/master/libs/beast/doc/html/index.html

https://medium.com/@sidhanthpandey/how-to-create-an-http-server-in-c-812cee49ff77

https://www.youtube.com/watch?v=gVmwrnhkybk

https://www.youtube.com/watch?v=ZSefPfZqxpo&list=PLbCUoS9rATH5SFX_AjH9_kZ9MNZgAHYNj

```