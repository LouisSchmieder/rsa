cmake_minimum_required(VERSION 3.21)
project(rsa C)

set(CMAKE_C_STANDARD 99)

add_library(library.c big/big.c big/big.h)
