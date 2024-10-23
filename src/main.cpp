#if defined(ARDUINO)
#include <Arduino.h>
#include <FFat.h>
#include <Wire.h>
#include <BLEDevice.h>
#include <nvs_flash.h>

#include "config.h"
#include "M5GFX.h"
#include "M5Unified.h"
#include "esp_camera.h"
#endif

#include "lvgl.h"
#if defined(ARDUINO)
#include "m5gfx_lvgl.h"
#else
#include "lvgl_port_m5stack.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#endif
#include "App.h"

#if !defined(ARDUINO)
M5GFX gfx;
#endif

void setup() {
#if defined(ARDUINO)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    USBSerial.begin(15200);
    M5.begin();

#if defined(M5CORES3)
    USBSerial.printf("M5CoreS3 User Demo, Version: %s\r\n", DEMO_VERSION);
#elif defined(M5CORES3SE)
    USBSerial.printf("M5CoreS3SE User Demo, Version: %s\r\n", DEMO_VERSION);
#endif

    // BM8563 Init (clear INT)
    M5.In_I2C.writeRegister8(0x51, 0x00, 0x00, 100000L);
    M5.In_I2C.writeRegister8(0x51, 0x01, 0x00, 100000L);
    M5.In_I2C.writeRegister8(0x51, 0x0D, 0x00, 100000L);

    // AW9523 Control BOOST
    M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN

#if MONKEY_TEST_ENABLE
    M5.Speaker.setAllChannelVolume(0);
#endif
    M5.Display.setBrightness(60);

    lv_init();
    m5gfx_lvgl_init();
#else
    gfx.init();

    lvgl_port_init(gfx);
#endif
    App_Init();
}

void loop() {
#if defined(ARDUINO)
    lv_timer_handler();
    delay(10);
#else
    usleep(10 * 000);
#endif
}
