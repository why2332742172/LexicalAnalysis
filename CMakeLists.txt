cmake_minimum_required(VERSION 3.20)
project(LexicalAnalysis)

set(CMAKE_CXX_STANDARD 14)

add_executable(LexicalAnalysis main.cpp GlobalVar.h init.cpp Utils.h analyse_first.cpp GlobalVar.cpp Utils.cpp analyse_second.cpp)
