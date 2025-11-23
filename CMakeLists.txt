cmake_minimum_required(VERSION 3.16)
project(LibraryApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DAL SHARED
        DAL/DalException.h
        DAL/User.h
        DAL/User.cpp
        DAL/Document.h
        DAL/Document.cpp
        DAL/Loan.h
        DAL/Loan.cpp
        DAL/IDataProvider.h
        DAL/JsonProvider.h
        DAL/JsonProvider.cpp
        DAL/EntityContext.h
        DAL/EntityContext.cpp
)

add_library(BLL SHARED
        BLL/DomainException.h
        BLL/Repository.h
        BLL/UserService.h
        BLL/UserService.cpp
        BLL/DocumentService.h
        BLL/DocumentService.cpp
        BLL/LoanService.h
        BLL/LoanService.cpp
)

add_executable(LibraryConsole
        PL/IView.h
        PL/ConsoleView.h
        PL/ConsoleView.cpp
        main.cpp
)
set(CMAKE_CTEST_ARGUMENTS "--verbose")

target_include_directories(DAL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(BLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(LibraryConsole PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(BLL PUBLIC DAL)
target_link_libraries(LibraryConsole PUBLIC BLL DAL)

add_subdirectory(tests)
