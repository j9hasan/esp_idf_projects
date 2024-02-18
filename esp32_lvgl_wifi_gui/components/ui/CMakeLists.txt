SET(SOURCES
    screens/ui_mainScreen.c
    screens/ui_setupScreen.c
    ui.c
    ui_events.c
    ui_helpers.c)
idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS .
                       REQUIRES lvgl shared_task wifi_app
                       )
