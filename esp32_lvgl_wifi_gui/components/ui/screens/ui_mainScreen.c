
#include "../ui.h"

void ui_mainScreen_screen_init(void)
{
    ui_mainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_mainScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    /* container for icons at top */
    ui_iconContainer = lv_obj_create(ui_mainScreen);
    lv_obj_set_align(ui_iconContainer, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_iconContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(ui_iconContainer, lv_pct(100));
    lv_obj_set_height(ui_iconContainer, lv_pct(10));
    lv_obj_set_style_bg_color(ui_iconContainer, lv_color_hex(0xB4E2FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_iconContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui_iconContainer, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_iconContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_iconContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* icons */
    ui_wifiIcon = lv_label_create(ui_iconContainer);
    lv_label_set_text(ui_wifiIcon, LV_SYMBOL_WIFI);
    lv_obj_align(ui_wifiIcon, LV_ALIGN_RIGHT_MID, -30, 0);
    lv_obj_add_flag(ui_wifiIcon, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_font(ui_wifiIcon, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsIcon = lv_label_create(ui_iconContainer);
    lv_label_set_text(ui_settingsIcon, LV_SYMBOL_SETTINGS);
    lv_obj_align(ui_settingsIcon, LV_ALIGN_RIGHT_MID, -5, 0);
    lv_obj_add_flag(ui_settingsIcon, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_font(ui_settingsIcon, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* main screen content */
    ui_label1 = lv_label_create(ui_mainScreen);
    lv_label_set_text(ui_label1, "Hello, this is lvgl v8.3.6 running on with esp32.");
    lv_label_set_long_mode(ui_label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_center(ui_label1);
    lv_obj_set_width(ui_label1, 300);

    /* bottom container */
    ui_bottomContainer = lv_obj_create(ui_mainScreen);
    lv_obj_set_align(ui_bottomContainer, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_bottomContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(ui_bottomContainer, lv_pct(100));
    lv_obj_set_height(ui_bottomContainer, lv_pct(9));
    lv_obj_set_style_bg_color(ui_bottomContainer, lv_color_hex(0xB4E2FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_bottomContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui_bottomContainer, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_bottomContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_bottomContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* events */
    lv_obj_add_event_cb(ui_settingsIcon, settings_icon_event_cb, LV_EVENT_CLICKED, NULL); /*Settings event callback*/
    // lv_obj_add_event_cb(ui_wifiIcon, wifi_icon_event_cb, LV_EVENT_CLICKED, NULL);         /*Assign an event callback*/
}

/*how to add styles*/
// static lv_style_t icon_style;
// lv_style_init(&icon_style);
// lv_style_set_bg_color(&icon_style, lv_color_hex(0xFF2400));
// lv_style_set_width(&icon_style, 20);
// lv_style_set_pad_right(&icon_style, 20);
// lv_obj_add_style(ui_settingsIcon, &icon_style, LV_PART_MAIN | LV_STATE_DEFAULT);