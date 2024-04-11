cmake_minimum_required(VERSION 3.24)
project(Sudoku)

set(CMAKE_CXX_STANDARD 17)

# On utilise le module PkgConfig pour détecter la librairie GTK+ sur le système
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)



# On dit à CMake d'utiliser GTK+, on indique au compilateur où trouver les fichiers headers
# Et au linker où trouver les librairies
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Instructions pour le compilateur
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})



find_package(LibXml2 REQUIRED)
add_compile_definitions(GTK PUBLIC ${LIBXML2_DEFINITIONS})
include_directories(PUBLIC ${LIBXML2_INCLUDE_DIRS})
link_libraries(${LIBXML2_LIBRARIES})


add_executable(Sudoku main.cpp conflit.h button.h Plan.h print_sudoku.h sudoku_algo.h SudokuInterface.h window.h sauvegarder_jeu.h)
TARGET_LINK_LIBRARIES(Sudoku ${GTK3_LIBRARIES})









