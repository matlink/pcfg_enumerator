# Version de cmake demandée.
cmake_minimum_required(VERSION 3.10)

project(PCFG)
 
# Chemin des répertoires contenant les fichiers entêtes.
include_directories(include)

# Chemin du répertoire contenant les binaires.
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -O3")

add_executable(pcfg
				src/main.cpp
				src/Simple.cpp
				src/Pcfg.cpp
				src/Preterm.cpp
				src/Rule.cpp
				src/Structure.cpp
				)

# Faire parler le make.
set(CMAKE_VERBOSE_MAKEFILE off)