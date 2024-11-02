#include <stdarg.h>
#include <stdio.h>
#include "HomeMenuView.h"

using namespace Page;

/*
    width: 60px
    height: 73px
*/


extern std::vector<UserApp> apps;

void HomeMenuView::Create(lv_obj_t* root) {
    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("background"));

    lv_obj_t * panel = lv_obj_create(root);
    lv_obj_set_size(panel, LV_HOR_RES, LV_VER_RES);
    lv_obj_center(panel);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW_WRAP);

    for (size_t i = 0; i < apps.size(); i++)
    {
        lv_obj_t* obj = lv_imgbtn_create(panel);
        // ui.imgbtn_list[i] = lv_imgbtn_create(root);
        // lv_obj_remove_style_all(ui.imgbtn_list[i]);
        lv_obj_set_size(obj, 60, 73);
        // lv_obj_set_pos(obj, 10 + 80 * (i % 4), 75 + 80 * (i / 4));


        lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, apps[i].icon, NULL);
        lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, apps[i].icon, NULL);

        // lv_obj_set_style_border_color(ui.imgbtn_list[i], lv_color_hex(0xff00ff), 0);
        // lv_obj_set_style_border_side(ui.imgbtn_list[i], LV_BORDER_SIDE_FULL, 0);
        // lv_obj_set_style_border_width(ui.imgbtn_list[i], 1, 0);
        // lv_obj_set_style_radius(ui.imgbtn_list[i], 0, 0);
        // lv_obj_set_style_border_post(ui.imgbtn_list[i], true, 0);
        ui.imgbtn_list.emplace_back(uiButton{obj, apps[i].className});
    }

    // ui.imgbtn_list[8] = lv_imgbtn_create(root);
    // lv_obj_set_size(ui.imgbtn_list[8], 60, 73);
    // lv_obj_set_pos(ui.imgbtn_list[8], 250, 10);

    // lv_imgbtn_set_src(ui.imgbtn_list[8], LV_IMGBTN_STATE_PRESSED, NULL, menu_img_pressed_list[8], NULL);
    // lv_imgbtn_set_src(ui.imgbtn_list[8], LV_IMGBTN_STATE_RELEASED, NULL, menu_img_pressed_list[8], NULL);

    // lv_obj_set_style_border_color(ui.imgbtn_list[8], lv_color_hex(0xff00ff), 0);
    // lv_obj_set_style_border_side(ui.imgbtn_list[8], LV_BORDER_SIDE_FULL, 0);
    // lv_obj_set_style_border_width(ui.imgbtn_list[8], 1, 0);
    // lv_obj_set_style_radius(ui.imgbtn_list[8], 0, 0);
    // lv_obj_set_style_border_post(ui.imgbtn_list[8], true, 0);

    ui.battery = BATTERY(root);
}

void HomeMenuView::Delete() {
}
