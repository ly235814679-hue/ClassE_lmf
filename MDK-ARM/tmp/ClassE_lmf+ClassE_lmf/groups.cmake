# groups.cmake

# group Application/MDK-ARM
add_library(Group_Application_MDK-ARM OBJECT
  "${SOLUTION_ROOT}/startup_stm32f103xb.s"
)
target_include_directories(Group_Application_MDK-ARM PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Application_MDK-ARM PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Application_MDK-ARM_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Application_MDK-ARM_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Application_MDK-ARM PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Application_MDK-ARM PUBLIC
  Group_Application_MDK-ARM_ABSTRACTIONS
)
set(COMPILE_DEFINITIONS
  STM32F10X_MD
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${SOLUTION_ROOT}/startup_stm32f103xb.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)

# group Application/User/Core
add_library(Group_Application_User_Core OBJECT
  "${SOLUTION_ROOT}/../Core/Src/main.c"
  "${SOLUTION_ROOT}/../Core/Src/gpio.c"
  "${SOLUTION_ROOT}/../Core/Src/adc.c"
  "${SOLUTION_ROOT}/../Core/Src/dma.c"
  "${SOLUTION_ROOT}/../Core/Src/spi.c"
  "${SOLUTION_ROOT}/../Core/Src/tim.c"
  "${SOLUTION_ROOT}/../Core/Src/usart.c"
  "${SOLUTION_ROOT}/../Core/Src/stm32f1xx_it.c"
  "${SOLUTION_ROOT}/../Core/Src/stm32f1xx_hal_msp.c"
)
target_include_directories(Group_Application_User_Core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Application_User_Core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Application_User_Core_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Application_User_Core_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Application_User_Core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Application_User_Core PUBLIC
  Group_Application_User_Core_ABSTRACTIONS
)
set_source_files_properties("${SOLUTION_ROOT}/../Core/Src/gpio.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Core/Src/adc.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Core/Src/dma.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Core/Src/spi.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Core/Src/tim.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Core/Src/usart.c" PROPERTIES
  COMPILE_OPTIONS ""
)

# group Drivers/STM32F1xx_HAL_Driver
add_library(Group_Drivers_STM32F1xx_HAL_Driver OBJECT
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c"
  "${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c"
)
target_include_directories(Group_Drivers_STM32F1xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Drivers_STM32F1xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Drivers_STM32F1xx_HAL_Driver_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Drivers_STM32F1xx_HAL_Driver_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Drivers_STM32F1xx_HAL_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Drivers_STM32F1xx_HAL_Driver PUBLIC
  Group_Drivers_STM32F1xx_HAL_Driver_ABSTRACTIONS
)
set_source_files_properties("${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c" PROPERTIES
  COMPILE_OPTIONS ""
)
set_source_files_properties("${SOLUTION_ROOT}/../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c" PROPERTIES
  COMPILE_OPTIONS ""
)

# group Drivers/CMSIS
add_library(Group_Drivers_CMSIS OBJECT
  "${SOLUTION_ROOT}/../Core/Src/system_stm32f1xx.c"
)
target_include_directories(Group_Drivers_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Drivers_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Drivers_CMSIS_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Drivers_CMSIS_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Drivers_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Drivers_CMSIS PUBLIC
  Group_Drivers_CMSIS_ABSTRACTIONS
)

# group lwrb
add_library(Group_lwrb OBJECT
  "${SOLUTION_ROOT}/../lwrb/lwrb/lwrb.c"
  "${SOLUTION_ROOT}/../lwrb/lwrb/lwrb_ex.c"
)
target_include_directories(Group_lwrb PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_lwrb PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_lwrb_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_lwrb_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_lwrb PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_lwrb PUBLIC
  Group_lwrb_ABSTRACTIONS
)

# group dwt_delay
add_library(Group_dwt_delay OBJECT
  "${SOLUTION_ROOT}/../dwt_delay/dwt_delay.c"
)
target_include_directories(Group_dwt_delay PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_dwt_delay PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_dwt_delay_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_dwt_delay_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_dwt_delay PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_dwt_delay PUBLIC
  Group_dwt_delay_ABSTRACTIONS
)

# group multibutton
add_library(Group_multibutton OBJECT
  "${SOLUTION_ROOT}/../multibutton/multi_button.c"
)
target_include_directories(Group_multibutton PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_multibutton PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_multibutton_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_multibutton_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_multibutton PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_multibutton PUBLIC
  Group_multibutton_ABSTRACTIONS
)

# group multimer
add_library(Group_multimer OBJECT
  "${SOLUTION_ROOT}/../multitimer/MultiTimer.c"
)
target_include_directories(Group_multimer PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_multimer PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_multimer_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_multimer_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_multimer PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_multimer PUBLIC
  Group_multimer_ABSTRACTIONS
)

# group Midware
add_library(Group_Midware OBJECT
  "${SOLUTION_ROOT}/../midware/src/app_event.c"
  "${SOLUTION_ROOT}/../midware/src/bsp_fan_pid.c"
  "${SOLUTION_ROOT}/../midware/src/bsp_multibutton.c"
  "${SOLUTION_ROOT}/../midware/src/bsp_ringbuffer.c"
  "${SOLUTION_ROOT}/../midware/src/bsp_soft_timer.c"
  "${SOLUTION_ROOT}/../midware/src/app_callbacks.c"
  "${SOLUTION_ROOT}/../midware/src/bsp_led.c"
  "${SOLUTION_ROOT}/../midware/src/bsp_relay.c"
  "${SOLUTION_ROOT}/../midware/src/bsp_sys_ctrl.c"
  "${SOLUTION_ROOT}/../midware/src/rf_matching.c"
  "${SOLUTION_ROOT}/../midware/src/command_parser.c"
)
target_include_directories(Group_Midware PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Midware PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Midware_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Midware_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Midware PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Midware PUBLIC
  Group_Midware_ABSTRACTIONS
)

# group pid
add_library(Group_pid OBJECT
  "${SOLUTION_ROOT}/../pid/PID.c"
)
target_include_directories(Group_pid PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_pid PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_pid_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_pid_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_pid PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_pid PUBLIC
  Group_pid_ABSTRACTIONS
)
