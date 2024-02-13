
set(SOURCES main.c )
#set(CMAKE_CXX_STANDARD 17)
idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS .
                       REQUIRES lvgl lvgl_esp32_drivers)

target_compile_definitions(${COMPONENT_LIB} PRIVATE LV_CONF_INCLUDE_SIMPLE=1)



