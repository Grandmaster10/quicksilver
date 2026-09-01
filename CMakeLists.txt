cmake_minimum_required(VERSION 3.17)
project(quicksilver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -pthread")

include_directories(src)

add_executable(simulator src/main.cpp src/parser/feed_handler.cpp)
add_executable(queue_bench bench/queue_bench.cpp)
add_executable(exchange_sim src/generators/exchange_sim.cpp)