set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)

# Some default GCC settings
set(TOOLCHAIN_PREFIX arm-none-eabi-)
set(FLAGS
    "-fdata-sections -ffunction-sections \
    --specs=nano.specs -Wl,--gc-sections -Og -g3 \
")



set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc ${FLAGS})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)