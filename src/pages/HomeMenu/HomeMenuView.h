#ifndef __HOMEMENU_VIEW_H
#define __HOMEMENU_VIEW_H

#include "../Page.h"

namespace Page {

class HomeMenuView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct BATTERY
    {
        private:
            lv_obj_t* label;
            lv_obj_t* bar;

        public:
            BATTERY() = default;
            BATTERY(lv_obj_t* root, int8_t val = 0) {
                bar = lv_bar_create(root);
                lv_obj_set_size(bar, 40, 15);
                lv_obj_align(bar, LV_ALIGN_TOP_LEFT, 10, 0);
                lv_bar_set_mode(bar, LV_BAR_MODE_RANGE);
                lv_bar_set_range(bar, 0, 100);

                label = lv_label_create(root);
                lv_obj_align(label, LV_ALIGN_TOP_LEFT, 60, 0);

                UpdateValue(0);
            }
            
            void UpdateValue(int8_t val, bool charging = false) {
                char buf[10];
                lv_bar_set_value(bar, val, LV_ANIM_ON);
                snprintf(buf, sizeof(buf), "%d%%", val);
                lv_label_set_text(label, buf);
            }
    };
    
    struct uiButton
    {
        lv_obj_t* btn;
        std::string appName;
    };
    
    struct {
        lv_obj_t* img_bg;
        BATTERY battery;
        std::vector<uiButton> imgbtn_list;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
