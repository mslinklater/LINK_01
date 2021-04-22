cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_kernel C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(pico_kernel
    main.c
	uart.c
	test.c
	ic6502.c
	shifter.c
	busmaster.c
	system.c
	usercommand.c
)

pico_enable_stdio_uart(pico_kernel 1)

pico_add_extra_outputs(pico_kernel)

target_link_libraries(pico_kernel pico_stdlib)
