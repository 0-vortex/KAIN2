cmake_minimum_required (VERSION 3.0)

project (KAIN2)

#Store the path to our CMAKE module folder in "CMAKE_MODULE_PATH".
#This is used by platform specific CMake scripts to correctly use external libraries.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMAKE")

#Toggles debug code on/off
set(DEBUG_VERSION 0 CACHE BOOL "Debug Version")

#Store the path to our game code folder in "GAME_CODE_DIR".
#This is used by platform specific CMake scripts to add this directory as an include directory.
string(CONCAT GAME_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR} "/GAME")

#Extract target architecture (MSVC only)
if (MSVC)
    if (CMAKE_CL_64)
        set(TARGET_ARCH "Win64")
    else()
        set(TARGET_ARCH "Win32")
    endif()
endif()

#We want to be able to group projects in folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Add game folder
add_subdirectory(GAME)