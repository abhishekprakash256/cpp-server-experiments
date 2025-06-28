cmake_minimum_required(VERSION 3.10)
project(BoostBeastWebSocket)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server ${Boost_LIBRARIES} pthread)
target_link_libraries(client ${Boost_LIBRARIES} pthread)