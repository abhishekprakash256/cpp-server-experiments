cmake_minimum_required(VERSION 3.10)
project(BoostBeastApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost libraries (adjust components as needed)
find_package(Boost REQUIRED COMPONENTS system thread)

# Add the executable
add_executable(boost_beast_app main.cpp)

# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})

# Link Boost libraries
target_link_libraries(boost_beast_app
    ${Boost_LIBRARIES}
    pthread
)