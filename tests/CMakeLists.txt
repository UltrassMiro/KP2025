cmake_minimum_required(VERSION 3.16)
project(LibraryTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(
        ${CMAKE_SOURCE_DIR}/external/googletest/googletest/include
        ${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include
)

enable_testing()

add_subdirectory(
        ${CMAKE_SOURCE_DIR}/external/googletest
        ${CMAKE_BINARY_DIR}/external/googletest
)


add_executable(library_tests
        User_tests.cpp
        Document_tests.cpp
        Loan_tests.cpp
        UserService_tests.cpp
        DocumentService_tests.cpp
        LoanService_tests.cpp
)

target_include_directories(library_tests PUBLIC
        ${CMAKE_SOURCE_DIR}/external/googletest/googletest/include
        ${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include
        ${CMAKE_SOURCE_DIR})

target_link_libraries(library_tests
        DAL
        BLL
        gtest
        gtest_main
        gmock
        gmock_main
)

include(GoogleTest)
gtest_discover_tests(library_tests)
