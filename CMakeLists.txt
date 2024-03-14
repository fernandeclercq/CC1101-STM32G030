# Template CMakeLists.txt configuration for STM32 MCUS
cmake_minimum_required(VERSION 3.22)


# Define the path of the cmake folder for custom cmake functions
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# Include the Toolchain file
include(GccArmNoneEabi)

# Include Doxygen
include(Docs)

message(${VSCODE_WORKSPACE_BASENAME})

# ##############################################################################
# Edit your MCU information up to the next border
project(${VSCODE_WORKSPACE_BASENAME} VERSION 0.0.1 LANGUAGES C) # Change "Template_STM32g0xx to your desired project name"

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app)

# Declare Configure.h Path For Project Definitions
set(CONFIGURE_FILE_INCLUDE_PATH "configured_files/include")


set(MCU_CLOCK_SPEED 16000000) # 16 MHz

math(EXPR MCU_CLOCK_CYCLE_NS "(1000000000 / ${MCU_CLOCK_SPEED}) ")


set(CONFIG_TARGET_STM32 1)

set(MCU_FAMILY STM32G0xx)
set(MCU_MODEL STM32G030xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m0plus
    -mthumb
    #-mfpu=
    #-mfloat-abi=
)
# Change the value of this variable to the exact name of the linker file in 'CubeMX'
set(MCU_LINKER_SCRIPT_NAME STM32G030F6Px_FLASH)


# Create a lowercase variable for the Startup Script Name
string(TOLOWER ${MCU_MODEL} STARTUP_SCRIPT_NAME)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/startup_${STARTUP_SCRIPT_NAME}.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/${MCU_LINKER_SCRIPT_NAME}.ld)

# ##############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})
enable_language(C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

#include "project_config.h to all source files"
add_definitions(-include ${CMAKE_CURRENT_SOURCE_DIR}/build/configured_files/include/project_config.h)


# Headers
set(CUBEMX_INCLUDE_DIRECTORIES
    #${CMAKE_CURRENT_SOURCE_DIR}/build/configured_files/include/   # Include the project config header 
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/STM32G0xx_LL/Inc         # Add 'Inc' folder for the LL headers (STM32G0xx)
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cc1101                 # Include header files for CC1101
)

    
set(PROJECT_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_DIR})
    
# Sources
file(GLOB_RECURSE STM32CUBEMX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/*.c # Add "Source Files" for the STM32g0x family
    ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/STM32G0xx_LL/Src/*.c     # Add "Src" folder for the LL sources (STM32G0xx)
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.c                 # Include header files for CC1101
)

file(GLOB_RECURSE PROJECT_SOURCES FOLLOW_SYMLINKS
    ${PROJECT_DIR}/*.c)



# Add configured files for Project
add_subdirectory(configured)

# Add 'app' subdirectory
add_subdirectory(app)


