
#ifndef _UI_H_
#define _UI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

    // SCREEN: ui_mainScreen

    extern void ui_mainScreen_screen_init(void);
    extern lv_obj_t *ui_mainScreen;

    /* containers */
    extern lv_obj_t *ui_iconContainer;
    extern lv_obj_t *ui_bottomContainer;

    /* icons */
    extern lv_obj_t *ui_wifiIcon;
    extern lv_obj_t *ui_settingsIcon;

    /* labels */
    extern lv_obj_t *ui_label1;

    /* buttons */

    /* events */
    void settings_icon_event_cb(lv_event_t *event);
    void wifi_icon_event_cb(lv_event_t *event);

    /* others */
    extern lv_obj_t *ui____initial_actions0;

    // SCREEN: ui_setupScreen
    extern lv_obj_t *tabview;
    extern void ui_setupScreen_screen_init(void);
    extern lv_obj_t *ui_setupScreen;
    extern lv_obj_t *ui_wifi_ssid_label;
    extern lv_obj_t *ui_wifi_ssid_dd;
    extern lv_obj_t *ui_wifi_pass_label;
    extern lv_obj_t *ui_wifi_pass_ta;
    extern lv_obj_t *ui_wifi_conn_btn;
    extern lv_obj_t *ui_wifi_conn_btn_label;
    extern lv_obj_t *ui_wifi_scan_btn;
    extern lv_obj_t *ui_wifi_scan_btn_label;
    extern lv_obj_t *ui_wifi_e_conn_btn;
    extern lv_obj_t *ui_wifi_e_conn_btn_label;
    extern lv_obj_t *ui_wifi_tab_label;

    /* event cb */
    void ui_wifi_scan_event_cb(lv_event_t *event);
    void ui_wifi_pass_ta_event_cb(lv_event_t *event);
    void ui_wifi_conn_event_cb(lv_event_t *event);

    /*glob*/
    void
    create_notif_panel(const char *title, const char *msg, bool _spin);
    void notif_msg_update(const char *msg);
    void notif_panel_del();

    extern lv_obj_t *notif_panel;
    extern lv_obj_t *notif_panel_title;
    extern lv_obj_t *notif_close_btn;
    extern lv_obj_t *notif_msg;
    extern lv_obj_t *notif_cross_icon;

    extern void kb_event_cb(lv_event_t *event);
    extern lv_obj_t *kb;

    void
    ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
