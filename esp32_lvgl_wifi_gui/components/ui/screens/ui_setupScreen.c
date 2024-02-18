
#include "../ui.h"

void ui_setupScreen_screen_init(void)
{
    lv_obj_t *label;

    void ui_event_ssid_dd(lv_event_t * e);
    void ui_event_pass_ta(lv_event_t * e);
    void ui_event_conn_btn(lv_event_t * e);
    void ui_event_econ_btn(lv_event_t * e);

    ui_setupScreen = lv_obj_create(NULL);

    tabview = lv_tabview_create(ui_setupScreen, LV_DIR_TOP, 50);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "tab 3");

    /*Add content to the tabs*/
    ui_wifi_ssid_label = lv_label_create(tab1);
    lv_obj_set_width(ui_wifi_ssid_label, lv_pct(13));
    lv_obj_set_height(ui_wifi_ssid_label, lv_pct(10));
    lv_obj_set_x(ui_wifi_ssid_label, lv_pct(-42));
    lv_obj_set_y(ui_wifi_ssid_label, lv_pct(-45));
    lv_obj_set_align(ui_wifi_ssid_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_ssid_label, "SSID:");

    ui_wifi_ssid_dd = lv_dropdown_create(tab1);
    lv_dropdown_set_options(ui_wifi_ssid_dd, "not connected");
    lv_obj_set_width(ui_wifi_ssid_dd, lv_pct(49));
    lv_obj_set_height(ui_wifi_ssid_dd, lv_pct(20));
    lv_obj_set_x(ui_wifi_ssid_dd, lv_pct(-7));
    lv_obj_set_y(ui_wifi_ssid_dd, lv_pct(-45));
    lv_obj_set_align(ui_wifi_ssid_dd, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_ssid_dd, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags

    ui_wifi_pass_label = lv_label_create(tab1);
    lv_obj_set_width(ui_wifi_pass_label, lv_pct(13));
    lv_obj_set_height(ui_wifi_pass_label, lv_pct(10));
    lv_obj_set_x(ui_wifi_pass_label, lv_pct(-42));
    lv_obj_set_y(ui_wifi_pass_label, lv_pct(-22));
    lv_obj_set_align(ui_wifi_pass_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_pass_label, "Pass:");

    ui_wifi_pass_ta = lv_textarea_create(tab1);
    lv_obj_set_width(ui_wifi_pass_ta, lv_pct(49));
    lv_obj_set_height(ui_wifi_pass_ta, lv_pct(20));
    lv_obj_set_x(ui_wifi_pass_ta, lv_pct(-7));
    lv_obj_set_y(ui_wifi_pass_ta, lv_pct(-22));
    lv_obj_set_align(ui_wifi_pass_ta, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_wifi_pass_ta, "Placeholder...");

    ui_wifi_conn_btn = lv_btn_create(tab1);
    lv_obj_set_width(ui_wifi_conn_btn, lv_pct(18));
    lv_obj_set_height(ui_wifi_conn_btn, lv_pct(15));
    lv_obj_set_x(ui_wifi_conn_btn, lv_pct(32));
    lv_obj_set_y(ui_wifi_conn_btn, lv_pct(-22));
    lv_obj_set_align(ui_wifi_conn_btn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_conn_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_wifi_conn_btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_wifi_conn_btn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_conn_btn_label = lv_label_create(ui_wifi_conn_btn);
    lv_obj_set_width(ui_wifi_conn_btn_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_conn_btn_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_wifi_conn_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_conn_btn_label, "Conn");

    ui_wifi_scan_btn = lv_btn_create(tab1);
    lv_obj_set_width(ui_wifi_scan_btn, lv_pct(18));
    lv_obj_set_height(ui_wifi_scan_btn, lv_pct(15));
    lv_obj_set_x(ui_wifi_scan_btn, lv_pct(32));
    lv_obj_set_y(ui_wifi_scan_btn, lv_pct(-45));
    lv_obj_set_align(ui_wifi_scan_btn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_scan_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_wifi_scan_btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_wifi_scan_btn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_scan_btn_label = lv_label_create(ui_wifi_scan_btn);
    lv_obj_set_width(ui_wifi_scan_btn_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_scan_btn_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_wifi_scan_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_scan_btn_label, "Scan");

    ui_wifi_e_conn_btn = lv_btn_create(tab1);
    lv_obj_set_width(ui_wifi_e_conn_btn, lv_pct(18));
    lv_obj_set_height(ui_wifi_e_conn_btn, lv_pct(15));
    lv_obj_set_x(ui_wifi_e_conn_btn, lv_pct(0));
    lv_obj_set_y(ui_wifi_e_conn_btn, lv_pct(20));
    lv_obj_set_align(ui_wifi_e_conn_btn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi_e_conn_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_wifi_e_conn_btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_wifi_e_conn_btn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi_e_conn_btn_label = lv_label_create(ui_wifi_e_conn_btn);
    lv_obj_set_width(ui_wifi_e_conn_btn_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_e_conn_btn_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_wifi_e_conn_btn_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_e_conn_btn_label, "Econ");

    ui_wifi_tab_label = lv_label_create(tab1);
    lv_obj_set_width(ui_wifi_tab_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_wifi_tab_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_wifi_tab_label, lv_pct(0));
    lv_obj_set_y(ui_wifi_tab_label, lv_pct(2));
    lv_obj_set_align(ui_wifi_tab_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifi_tab_label, "Click to connect from EEPROM");

    label = lv_label_create(tab2);
    lv_label_set_text(label, "Second tab");

    label = lv_label_create(tab3);
    lv_label_set_text(label, "Third tab");
    lv_tabview_set_act(tabview, 0, LV_ANIM_ON);

    lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);

    /* events */
    lv_obj_add_event_cb(ui_wifi_pass_ta, ui_wifi_pass_ta_event_cb, LV_EVENT_CLICKED, NULL); /*Settings event callback*/
    lv_obj_add_event_cb(ui_wifi_scan_btn, ui_wifi_scan_event_cb, LV_EVENT_CLICKED, NULL);   /*Settings event callback*/
    lv_obj_add_event_cb(ui_wifi_conn_btn, ui_wifi_conn_event_cb, LV_EVENT_CLICKED, NULL);   /*Settings event callback*/
}

/*how to add styles*/
// static lv_style_t icon_style;
// lv_style_init(&icon_style);
// lv_style_set_bg_color(&icon_style, lv_color_hex(0xFF2400));
// lv_style_set_width(&icon_style, 20);
// lv_style_set_pad_right(&icon_style, 20);
// lv_obj_add_style(ui_settingsIcon, &icon_style, LV_PART_MAIN | LV_STATE_DEFAULT);