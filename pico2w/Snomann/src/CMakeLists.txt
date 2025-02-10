add_executable(${NAME}
#        main.cpp
#        main_rp2040.cpp
        main_PicoW.cpp
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
	 pico_stdlib
#         pico_cyw43_arch_none
         FreeRTOS-Kernel-Heap4
	)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(${NAME} pico_cyw43_arch_none)
endif()
	
target_include_directories(${NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
     )
     
target_compile_definitions(${NAME} PRIVATE
    configNUM_CORES=1
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 0)
pico_enable_stdio_uart(${NAME} 1)