configure_file(
    "project_config.h.in"
    "${CMAKE_BINARY_DIR}/${CONFIGURE_FILE_INCLUDE_PATH}/project_config.h" ESCAPE_QUOTES
)