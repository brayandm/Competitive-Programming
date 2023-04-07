cmake_minimum_required(VERSION 3.24)
project(icpc)

set(CMAKE_CXX_STANDARD 17)

set(filename)

foreach(number RANGE 97 122 1)
    string(ASCII ${number} filename)
    file(WRITE codes/${filename}.cpp)
    add_executable(${filename} codes/${filename}.cpp)

endforeach()

