cmake_minimum_required(VERSION 3.27)
project(test)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(${PROJECT_NAME} test.cpp test.h ../Unique_ptr.h ../Shared_ptr.h ../MemorySpan.h
        ../MsPtr.h) # просто тесты
add_executable(leak_${PROJECT_NAME} test.cpp test.h ../Unique_ptr.h ../Shared_ptr.h ../MemorySpan.h
        ../MsPtr.h) # тесты с утечкой памяти

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(leak_${PROJECT_NAME} gtest gtest_main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_options(leak_${PROJECT_NAME} PRIVATE -fsanitize=address) # флаг для поиска утечек памяти
include(GoogleTest)
gtest_discover_tests(test)