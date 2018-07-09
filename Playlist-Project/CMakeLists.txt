cmake_minimum_required(VERSION 3.10)
project(p4)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(p4
        playlist.cc
        playlist.h
        playlist_test.cc)
