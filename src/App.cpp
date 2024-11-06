#include "PageManager.h"
#include "res/ResourcePool.h"
#include "pages/AppFactory.h"
#include "NotificationBar.h"

extern std::vector<UserApp> apps;

lv_style_t NotificationBar::m_notifPanelStyle;
lv_obj_t * NotificationBar::m_notifPanel;
std::vector<NotificationBar::ICON> NotificationBar::m_left_container;
std::vector<NotificationBar::ICON> NotificationBar::m_middle_container;
std::vector<NotificationBar::ICON> NotificationBar::m_right_container;

NotificationBar::NotificationBar() {
    lv_style_init(&m_notifPanelStyle);
    lv_style_set_width(&m_notifPanelStyle, LV_PCT(100));
    lv_style_set_height(&m_notifPanelStyle, NOTIFICATION_BAR_HEIGHT);
    lv_style_set_border_color(&m_notifPanelStyle, lv_color_make(238, 238, 238));
    lv_style_set_border_width(&m_notifPanelStyle, 0);
    lv_style_set_outline_width(&m_notifPanelStyle, 0);
    lv_style_set_pad_all(&m_notifPanelStyle, 0);
    
    m_notifPanel = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(m_notifPanel);
    lv_obj_add_style(m_notifPanel, &m_notifPanelStyle, LV_PART_MAIN);
    // Optional: Set a background color for the status bar
    lv_obj_set_style_bg_color(m_notifPanel, lv_color_hex(0x333333), 0);
    lv_obj_set_style_bg_opa(m_notifPanel, LV_OPA_COVER, 0);
    lv_obj_align(m_notifPanel, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_clear_flag(m_notifPanel, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_move_foreground(m_notifPanel);

    // Left container (for left-aligned icons)
    lv_obj_t * lobj = lv_obj_create(m_notifPanel);
    lv_obj_set_size(lobj, LV_PCT(100) / 3, 20);
    lv_obj_align(lobj, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_clear_flag(lobj, LV_OBJ_FLAG_SCROLLABLE); // Disable scrolling
    lv_obj_set_flex_flow(lobj, LV_FLEX_FLOW_ROW); // Align children left to right
    m_left_container.emplace_back(std::make_pair(ICON_TYPE::ROOT, lobj)); 

    // Middle container (for centered time display)
    lv_obj_t * mobj = lv_obj_create(m_notifPanel);
    lv_obj_set_size(mobj, LV_PCT(100) / 3, 20);
    lv_obj_align(mobj, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(mobj, LV_OBJ_FLAG_SCROLLABLE);
    m_middle_container.emplace_back(std::make_pair(ICON_TYPE::ROOT, mobj)); 

    // Right container (for right-aligned icons)
    lv_obj_t * robj = lv_obj_create(m_notifPanel);
    lv_obj_set_size(robj, LV_PCT(100) / 3, 20);
    lv_obj_align(robj, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_clear_flag(robj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(robj, LV_FLEX_FLOW_ROW_REVERSE); // Align children right to left
    m_right_container.emplace_back(std::make_pair(ICON_TYPE::ROOT, robj)); 


    lv_obj_t * time_label = lv_label_create(m_middle_container[0].second);
    lv_label_set_text(time_label, "12:00"); // Placeholder text
    lv_obj_center(time_label);
    m_middle_container.emplace_back(std::make_pair(ICON_TYPE::TIME, time_label));  

    lv_obj_t * left_icon = lv_label_create(m_left_container[0].second);
    lv_label_set_text(left_icon, LV_SYMBOL_WIFI);
    m_left_container.emplace_back(std::make_pair(ICON_TYPE::WIFI, left_icon));  

    lv_obj_t * right_icon = lv_label_create(m_right_container[0].second);
    lv_label_set_text(right_icon, LV_SYMBOL_BATTERY_FULL);
    m_right_container.emplace_back(std::make_pair(ICON_TYPE::BATTERY, right_icon));  

};

NotificationBar::~NotificationBar()
{
    lv_timer_del(m_timer);
    lv_obj_del_async(m_notifPanel);
}

void NotificationBar::Refresh(lv_timer_t * m_timer)
{
    NotificationBar* bar = (NotificationBar*)m_timer->user_data;
    
    for (auto& icon : bar->m_left_container)
        Update(icon);

    for (auto& icon : bar->m_middle_container)
        Update(icon);        

    for (auto& icon : bar->m_right_container)
        Update(icon);
};

void NotificationBar::Update(NotificationBar::ICON& icon)
{
    printf("Notification bar update %d\n", icon.first);
    switch (icon.first)
    {
    case ICON_TYPE::ROOT:
        break;

    case ICON_TYPE::WIFI:
        lv_label_set_text(icon.second, LV_SYMBOL_WIFI);
        break;

    case ICON_TYPE::BATTERY:
        lv_label_set_text(icon.second, LV_SYMBOL_BATTERY_FULL);
        break;

    case ICON_TYPE::TIME:
        {
            char buf[6];
            lv_snprintf(buf, sizeof(buf), "%02d:%02d", lv_tick_get() / 60000 % 24, lv_tick_get() / 1000 % 60);
            lv_label_set_text(icon.second, buf);
        }
        break;

    case ICON_TYPE::SD_CARD:
        break;  

    case ICON_TYPE::ERROR:
        break;  

    default:
        break;
    }
}

void NotificationBar::Start()
{
    m_timer = lv_timer_create(Refresh, 1000, this);
}


void App_Notification()
{
    static NotificationBar notifier;
    notifier.Start();
}

void App_MainPage()
{
    /* Set root default style */
    static lv_style_t mainPanelStyle;
    lv_style_init(&mainPanelStyle);
    lv_style_set_width(&mainPanelStyle, LV_PCT(100));
    lv_style_set_height(&mainPanelStyle, LV_VER_RES-NOTIFICATION_BAR_HEIGHT);
    lv_style_set_border_color(&mainPanelStyle, lv_color_make(238, 238, 238));
    lv_style_set_border_width(&mainPanelStyle, 0);
    lv_style_set_outline_width(&mainPanelStyle, 0);
    lv_style_set_pad_all(&mainPanelStyle, 0);

    static lv_obj_t * mainPanel = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(mainPanel);
    lv_obj_add_style(mainPanel, &mainPanelStyle, LV_PART_MAIN);
    lv_obj_align(mainPanel, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_flag(mainPanel, LV_OBJ_FLAG_SCROLLABLE);

    static AppFactory factory;
    static PageManager manager(&factory, mainPanel);
    manager.SetRootDefaultStyle(&mainPanelStyle);

    /* Initialize resource pool */
    ResourcePool::Init();

    /* Initialize pages */
    manager.Install("StartUp");
    manager.Install("HomeMenu");

    for (size_t i = 0; i < apps.size(); i++) {
        manager.Install(apps[i].className.c_str());
    }

    manager.SetGlobalLoadAnimType(PageManager::LOAD_ANIM_NONE);

    manager.Push("StartUp");
}

void App_Init() {
    /* Make sure the default group exists */
    if (!lv_group_get_default()) {
        lv_group_t* group = lv_group_create();
        lv_group_set_default(group);
    }

    /* Set screen style */
    lv_obj_t* scr = lv_scr_act();
    lv_obj_remove_style_all(scr);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_white());

    App_Notification();

    App_MainPage();
}

void App_Uninit() {
}
