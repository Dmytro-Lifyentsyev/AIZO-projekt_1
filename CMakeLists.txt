cmake_minimum_required (VERSION 3.10)
project ("Projekt_1")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)    
    add_compile_options(/W4 /WX)
else()    
    add_compile_options(-Wall -Wextra -Werror)
endif()

add_executable(Projekt_1 
    "Projekt_1/src/main.cpp" 
    "Projekt_1/include/Parameters.h"
    "Projekt_1/include/Tablica.hpp"
    "Projekt_1/include/List.hpp"
    "Projekt_1/include/Lista_dk.hpp"
    "Projekt_1/include/Reader_Writer.hpp" 
    "Projekt_1/include/Weryfikator.hpp"
    "Projekt_1/include/Quick_sort.hpp"
    "Projekt_1/include/Shell_sort.hpp"
    "Projekt_1/include/Bucket_sort.hpp"
    "Projekt_1/include/Stoper.hpp"
    "Projekt_1/include/ZapisCSV.hpp"
    "Projekt_1/include/Eksperyment.hpp"
    "Projekt_1/include/Generator.hpp"
    "Projekt_1/include/Stos.hpp"
    "Projekt_1/include/BST.hpp"
    "Projekt_1/include/Quick_sort_stos.hpp"
)

if(UNIX)
    target_include_directories(Projekt_1 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Projekt_1/include")
    target_link_directories(Projekt_1 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Projekt_1/lib")
    target_link_libraries(Projekt_1 PRIVATE parameters)
    
    set_target_properties(Projekt_1 PROPERTIES
        BUILD_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/Projekt_1/lib"
        INSTALL_RPATH "$ORIGIN/lib"
    )
else()
endif()