# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(opencl LANGUAGES CXX)

add_executable(平台信息 平台信息 .cpp)