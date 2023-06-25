cmake_minimum_required(VERSION 3.25)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP_Project main.cpp cpp/Image.cpp hpp/Image.hpp hpp/Pixel.hpp cpp/Session.cpp hpp/Session.hpp cpp/Controller.cpp hpp/Controller.hpp cpp/Command.cpp hpp/Command.hpp)
