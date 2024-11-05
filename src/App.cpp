#include "PageManager.h"
#include "res/ResourcePool.h"
#include "pages/AppFactory.h"

extern std::vector<UserApp> apps;

#define NOTIFICATION_BAR_HEIGHT      20

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

    static lv_style_t notifPanelStyle;
    lv_style_init(&notifPanelStyle);
    lv_style_set_width(&notifPanelStyle, LV_PCT(100));
    lv_style_set_height(&notifPanelStyle, NOTIFICATION_BAR_HEIGHT);
    lv_style_set_border_color(&notifPanelStyle, lv_color_make(238, 238, 238));
    lv_style_set_border_width(&notifPanelStyle, 0);
    lv_style_set_outline_width(&notifPanelStyle, 0);
    lv_style_set_pad_all(&notifPanelStyle, 0);

    static lv_obj_t * notifPanel = lv_obj_create(scr);
    lv_obj_remove_style_all(notifPanel);
    lv_obj_add_style(notifPanel, &notifPanelStyle, LV_PART_MAIN);
    // Optional: Set a background color for the status bar
    lv_obj_set_style_bg_color(notifPanel, lv_color_hex(0x333333), 0);
    lv_obj_set_style_bg_opa(notifPanel, LV_OPA_COVER, 0);
    lv_obj_align(notifPanel, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_clear_flag(notifPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_move_foreground(notifPanel);

    /* Set root default style */
    static lv_style_t mainPanelStyle;
    lv_style_init(&mainPanelStyle);
    lv_style_set_width(&mainPanelStyle, LV_PCT(100));
    lv_style_set_height(&mainPanelStyle, LV_VER_RES-NOTIFICATION_BAR_HEIGHT);
    lv_style_set_border_color(&mainPanelStyle, lv_color_make(238, 238, 238));
    lv_style_set_border_width(&mainPanelStyle, 0);
    lv_style_set_outline_width(&mainPanelStyle, 0);
    lv_style_set_pad_all(&mainPanelStyle, 0);

    static lv_obj_t * mainPanel = lv_obj_create(scr);
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

void App_Uninit() {
}
