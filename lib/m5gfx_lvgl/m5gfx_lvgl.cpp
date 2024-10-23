
#include "m5gfx_lvgl.h"

#if defined(ARDUINO)
SemaphoreHandle_t xGuiSemaphore;
static lv_disp_draw_buf_t draw_buf;

LV_IMG_DECLARE(cursor_hand);

static void m5gfx_lvgl_flush(lv_disp_drv_t *disp, const lv_area_t *area,
                             lv_color_t *color_p) {
    int w = (area->x2 - area->x1 + 1);
    int h = (area->y2 - area->y1 + 1);

    M5.Display.startWrite();
    M5.Display.setAddrWindow(area->x1, area->y1, w, h);
    M5.Display.writePixels((lgfx::swap565_t *)&color_p->full, w * h);
    M5.Display.endWrite();
    lv_disp_flush_ready(disp);
}

static void m5gfx_lvgl_read(lv_indev_drv_t *indev_driver,
                            lv_indev_data_t *data) {
    uint16_t touchX, touchY;
    lgfx::touch_point_t tp[1];

    M5.update();

    M5.Display.getTouchRaw(&touchX, &touchY);

    int nums = M5.Display.getTouchRaw(tp, 1);
    if (nums) {
        data->state   = LV_INDEV_STATE_PR;
        data->point.x = tp[0].x;
        data->point.y = tp[0].y;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    // bool touched = M5.Display.getTouch(&touchX, &touchY);
    // if (!touched) {
    //     data->state = LV_INDEV_STATE_REL;
    // } else {
    //     data->state   = LV_INDEV_STATE_PR;
    //     data->point.x = touchX;
    //     data->point.y = touchY;
    // }
}

static void lvgl_tick_task(void *arg) {
    (void)arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

void m5gfx_lvgl_init(void) {
    static lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(
        LCD_WIDTH * 80 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    static lv_color_t *buf2 = (lv_color_t *)heap_caps_malloc(
        LCD_WIDTH * 80 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);

    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, LCD_WIDTH * 80);
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res  = LCD_WIDTH;
    disp_drv.ver_res  = LCD_HEIGHT;
    disp_drv.flush_cb = m5gfx_lvgl_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = m5gfx_lvgl_read;
    lv_indev_t *indev = lv_indev_drv_register(&indev_drv);

    // Uncomment this to enable cursor icon
    // lv_obj_t *cursor  = lv_img_create(lv_scr_act());
    // lv_img_set_src(cursor, &cursor_hand);
    // lv_indev_set_cursor(indev, cursor);

    xGuiSemaphore                                     = xSemaphoreCreateMutex();
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lvgl_tick_task, .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(
        esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
}
#endif