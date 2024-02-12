target_sources(${MCUX_SDK_PROJECT_NAME} PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/freertos_hello.c
  ${CMAKE_CURRENT_LIST_DIR}/FreeRTOSConfig.h
  ${CMAKE_CURRENT_LIST_DIR}/versionInfo.c
)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/
)

set_source_files_properties("${CMAKE_CURRENT_LIST_DIR}/FreeRTOSConfig.h" PROPERTIES COMPONENT_CONFIG_FILE "middleware_freertos-kernel_template")