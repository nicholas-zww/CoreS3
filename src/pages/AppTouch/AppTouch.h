#ifndef __APPTOUCH_PRESENTER_H
#define __APPTOUCH_PRESENTER_H

#include "AppTouchView.h"
#if defined(ARDUINO)
#include "AppTouchModel.h"
#endif
namespace Page {

class AppTouch : public PageBase {
   public:
    AppTouch();
    virtual ~AppTouch();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewUnload();
    virtual void onViewDidUnload();

   private:
    void Update();
    void AttachEvent(lv_obj_t* obj) {
        AttachEvent(obj, LV_EVENT_ALL);
    }
    void AttachEvent(lv_obj_t* obj, lv_event_code_t code);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

    void ClearTouchPoint(void) {
        #if defined(ARDUINO)
        t_prev.x = 0;
        t_prev.y = 0;
        #endif
    }

   private:
    AppTouchView View;
#if defined(ARDUINO)
    AppTouchModel Model;
    m5gfx::touch_point_t t_prev;
#endif
    lv_timer_t* timer;
};

}  // namespace Page

#endif
