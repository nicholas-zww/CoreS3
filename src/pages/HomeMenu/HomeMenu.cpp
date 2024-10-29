#include "HomeMenu.h"
#include <sstream>

using namespace Page;

HomeMenu::HomeMenu() : timer(nullptr) {
}

HomeMenu::~HomeMenu() {
}

void HomeMenu::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewLoad() {
    LV_LOG_USER(__func__);

    View.Create(_root);

    for (size_t i = 0; i < 9; i++) {
        AttachEvent(View.ui.imgbtn_list[i], LV_EVENT_CLICKED);
    }
}

void HomeMenu::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 1000, this);
}

void HomeMenu::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void HomeMenu::onViewUnload() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void HomeMenu::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void HomeMenu::Update() {
#if defined(ARDUINO)
    View.ui.battery.UpdateValue(M5.Power.getBatteryLevel(), M5.Power.isCharging() == m5::Power_Class::is_charging_t::is_charging);
#else
    View.ui.battery.UpdateValue(50);
#endif
}

void HomeMenu::onTimerUpdate(lv_timer_t* timer) {
    HomeMenu* instance = (HomeMenu*)timer->user_data;

    instance->Update();
}

void HomeMenu::onEvent(lv_event_t* event) {
    HomeMenu* instance = (HomeMenu*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        if (obj == instance->View.ui.imgbtn_list[2]) {
            instance->_Manager->Replace("Pages/AppMic");
            return;
        }
        // M5.Speaker.playWav((const uint8_t*)ResourcePool::GetWav("select_0_5s"),
        //                    ~0u, 1, 1);
        if (obj == instance->View.ui.imgbtn_list[0]) {
            instance->_Manager->Replace("Pages/AppWiFi");
        } 
        else if (obj == instance->View.ui.imgbtn_list[1]) {
            instance->_Manager->Replace("Pages/AppCamera");
        }else if (obj == instance->View.ui.imgbtn_list[4]) {
            instance->_Manager->Replace("Pages/AppIMU");
        }  
        else if (obj == instance->View.ui.imgbtn_list[3]) {
            instance->_Manager->Replace("Pages/AppPower");
        } else if (obj == instance->View.ui.imgbtn_list[5]) {
            instance->_Manager->Replace("Pages/AppSD");
        } else if (obj == instance->View.ui.imgbtn_list[6]) {
            instance->_Manager->Replace("Pages/AppTouch");
        } else if (obj == instance->View.ui.imgbtn_list[7]) {
            instance->_Manager->Replace("Pages/AppI2C");
        } else if (obj == instance->View.ui.imgbtn_list[8]) {
            instance->_Manager->Replace("Pages/AppRTC");
        }
    }
}
