# Executable files
add_executable(${EXECUTABLE}
    main.c
    ${STM32CUBEMX_SOURCES} 
    ${STARTUP_SCRIPT}
)

# Embedded macros(defines)
target_compile_definitions(${EXECUTABLE} PRIVATE
    ${MCU_MODEL}
)

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE} PRIVATE
    ${CUBEMX_INCLUDE_DIRECTORIES}
    ${PROJECT_INCLUDE_DIRECTORIES}

    # Include directory for the Config.h file (Project Information)
    ${CMAKE_BINARY_DIR}/${CONFIGURE_FILE_INCLUDE_PATH}
    
)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    message("Compiling with Debug Flags: -Wall -Wextra -Wpedantic -Wno-unused-parameter -Og -g3 -ggdb")
    set(COMPILER_FLAGS 
            "-Wall" 
            "-Wextra" 
            "-Wpedantic" 
            "-Wno-unused-parameter" 
            "-Og" 
            "-g3" 
            "-ggdb"
        )

elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
    message("Compiling with Release Flags: -Wall -Wextra -Wpedantic -Wno-unused-parameter -Werror -Wfatal-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -O3")
    set(COMPILER_FLAGS 
            "-Wall" 
            "-Wextra" 
            "-Wpedantic" 
            "-Wno-unused-parameter" 
            #"-Werror"
            "-Wfatal-errors"
            "-Wmissing-include-dirs"
            "-Wswitch-default"
            "-Wswitch-enum"
            "-Wconversion"
            "-O3"
        )

elseif(${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
    message("Compiling with Release Minimal Size Flags: -Wall -Wextra -Wpedantic -Wno-unused-parameter -Werror -Wfatal-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -Os")
    set(COMPILER_FLAGS 
        "-Wall" 
        "-Wextra" 
        "-Wpedantic" 
        "-Wno-unused-parameter" 
        #"-Werror"
        "-Wfatal-errors"
        "-Wmissing-include-dirs"
        "-Wswitch-default"
        "-Wswitch-enum"
        "-Wconversion"
        "-Os"
        )

elseif(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
    message("Compiling with Release Fast Speed Flags: -Wall -Wextra -Wpedantic -Wno-unused-parameter -Werror -Wfatal-errors -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wconversion -Ofast")
    set(COMPILER_FLAGS 
        "-Wall" 
        "-Wextra" 
        "-Wpedantic" 
        "-Wno-unused-parameter" 
        #"-Werror"
        "-Wfatal-errors"
        "-Wmissing-include-dirs"
        "-Wswitch-default"
        "-Wswitch-enum"
        "-Wconversion"
        "-Ofast"
    )

endif()


# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    ${COMPILER_FLAGS}
)

# Use Low-Level Drivers Flag
target_compile_definitions(
        ${EXECUTABLE}
        PRIVATE
        "USE_FULL_LL_DRIVER"
    )


target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)



add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)



add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)


