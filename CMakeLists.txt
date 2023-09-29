cmake_minimum_required(VERSION 3.2)

project(menu)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

option(MENU_TEST "Compile tests?" ON)
option(MENU_EXAMPLE "Compile examples?" ON)

add_subdirectory(./3rd_party)
add_subdirectory(./src)

if(MENU_TEST)
   add_subdirectory(./test)
endif()
if(MENU_EXAMPLE)
   add_subdirectory(./example)
endif()