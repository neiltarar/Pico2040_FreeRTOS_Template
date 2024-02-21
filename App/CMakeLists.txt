cmake_minimum_required(VERSION 3.15)

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${APP_1_NAME}")
add_compile_definitions(APP_VERSION="${APP_1_VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${BUILD_NUMBER})

# Include app source code file(s)
add_executable(${APP_1_NAME}
    ${APP_1_SRC_DIRECTORY}/main.c
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APP_1_NAME} 1)
pico_enable_stdio_uart(${APP_1_NAME} 0)

# Link to built libraries (gpio, time, etc. functions)
target_link_libraries(
    ${APP_1_NAME}
    pico_stdlib
    FreeRTOS
    )

# Enable extra build products - create map - bin - hex -uf2 files needed to upload to Pico
pico_add_extra_outputs(${APP_1_NAME})