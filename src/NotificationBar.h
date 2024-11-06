#pragma once
#include "lvgl.h"
#include <vector>

#define NOTIFICATION_BAR_HEIGHT      20

class NotificationBar {
    public:
        enum ICON_TYPE : int
        {
            ROOT = 0,
            WIFI,
            BATTERY,
            TIME,
            SD_CARD,
            ERROR,
        };

        using ICON = std::pair<ICON_TYPE, lv_obj_t *>;

        NotificationBar();
        ~NotificationBar();

        static void Refresh(lv_timer_t * m_timer);

        void Start();

    private:

        static void Update(ICON& icon);

        static lv_style_t m_notifPanelStyle;
        static lv_obj_t * m_notifPanel;
        static std::vector<ICON> m_left_container;
        static std::vector<ICON> m_middle_container;
        static std::vector<ICON> m_right_container;
        lv_timer_t * m_timer;
};
