SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    images/ui_img_samplepngimage_100kbmb_png.c
    ui_helpers.c)

idf_component_register(SRCS ${SOURCES}
                      INCLUDE_DIRS .
                      REQUIRES lvgl)
