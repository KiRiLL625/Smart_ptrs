cmake_minimum_required(VERSION 3.27)
project(Smart_ptrs)

set(CMAKE_CXX_STANDARD 17)

add_executable(Smart_ptrs main.cpp
        Unique_ptr.h
        Shared_ptr.h
        MemorySpan.h
        MsPtr.h)

add_subdirectory(googletest)
add_subdirectory(testing)

install(TARGETS Smart_ptrs DESTINATION bin)