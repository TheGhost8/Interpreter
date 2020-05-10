cmake_minimum_required(VERSION 3.1)
project(Interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(Interpreter main.cpp flex.cpp flex.h parser.h parser.cpp interpreter.h interpreter.cpp variable.h variable.cpp operations.h operations.cpp type_tables.cpp type_tables.h data.cpp data.h)