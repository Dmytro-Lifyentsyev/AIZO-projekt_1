cmake_minimum_required (VERSION 3.10)

project ("Projekt_1")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

include_directories("Projekt_1/include")

add_executable(Projekt_1 "Projekt_1/src/main.cpp" "Projekt_1/include/List.h" "Projekt_1/include/Reader.h" "Projekt_1/include/Weryfikator.h")