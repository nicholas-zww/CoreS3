/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "Page.h"
#include "AppFactory.h"
#include "StartUp/StartUp.h"
#include "HomeMenu/HomeMenu.h"

#include "AppWiFi/AppWiFi.h"
#include "AppCamera/AppCamera.h"
#include "AppMic/AppMic.h"
#include "AppPower/AppPower.h"
#include "AppIMU/AppIMU.h"
#include "AppSD/AppSD.h"
#include "AppTouch/AppTouch.h"
#include "AppI2C/AppI2C.h"
#include "AppRTC/AppRTC.h"

std::vector<UserApp> apps;

#define REG_PAGE(classname)     creators[#classname] = [](){return new Page::classname;}    

LV_IMG_DECLARE(menu_wifi);
LV_IMG_DECLARE(menu_cam);
LV_IMG_DECLARE(menu_mic);
LV_IMG_DECLARE(menu_power);
LV_IMG_DECLARE(menu_imu);
LV_IMG_DECLARE(menu_sd);
LV_IMG_DECLARE(menu_touch);
LV_IMG_DECLARE(menu_i2c);
LV_IMG_DECLARE(menu_sys);

AppFactory::AppFactory() {
    REG_PAGE(StartUp);
    REG_PAGE(HomeMenu);
    REG_PAGE(AppWiFi);
    REG_PAGE(AppCamera);
    // REG_PAGE(AppMic);
    REG_PAGE(AppPower);
    REG_PAGE(AppIMU);
    REG_PAGE(AppSD);
    REG_PAGE(AppTouch);
    REG_PAGE(AppI2C);
    REG_PAGE(AppRTC);

    apps.clear();
    apps.emplace_back(UserApp{"AppWiFi", &menu_wifi, Maybe<std::string>("AppRTC"), Maybe<std::string>("AppCamera"), Maybe<std::string>("HomeMenu")});
    apps.emplace_back(UserApp{"AppCamera", &menu_cam, Maybe<std::string>("AppWiFi"), Maybe<std::string>("AppPower"), Maybe<std::string>("HomeMenu")});
    // apps.emplace_back(UserApp{"AppMic", &menu_mic, Maybe<std::string>::Nothing(), Maybe<std::string>("HomeMenu"), Maybe<std::string>("HomeMenu")});
    apps.emplace_back(UserApp{"AppPower", &menu_power, Maybe<std::string>("AppCamera"), Maybe<std::string>("AppIMU"), Maybe<std::string>("HomeMenu")});
    apps.emplace_back(UserApp{"AppIMU", &menu_imu, Maybe<std::string>("AppPower"), Maybe<std::string>("AppSD"), Maybe<std::string>("HomeMenu")});
    apps.emplace_back(UserApp{"AppSD", &menu_sd, Maybe<std::string>("AppIMU"), Maybe<std::string>("AppTouch"), Maybe<std::string>("HomeMenu")});
    apps.emplace_back(UserApp{"AppTouch", &menu_touch, Maybe<std::string>("AppSD"), Maybe<std::string>("AppI2C"), Maybe<std::string>("HomeMenu")});
    apps.emplace_back(UserApp{"AppI2C", &menu_i2c, Maybe<std::string>("AppTouch"), Maybe<std::string>("AppWiFi"), Maybe<std::string>("HomeMenu")});
    // apps.emplace_back(UserApp{"AppRTC", &menu_sys, Maybe<std::string>("AppI2C"), Maybe<std::string>("AppWiFi"), Maybe<std::string>("HomeMenu")});
}

PageBase* AppFactory::CreatePage(const char* name) {
    auto it = creators.find(name);
    if (it != creators.end()) {
        return it->second();
    }
    return nullptr;
}

Maybe<std::string> AppFactory::GetNextPage(const std::string& name) {
    for (const auto &a : apps) {
        if (a.className == name)
            return a.nextPage;
    }
    return Maybe<std::string>::Nothing();
}

Maybe<std::string> AppFactory::GetPreviousPage(const std::string& name) {
    for (const auto &a : apps) {
        if (a.className == name)
            return a.prePage;
    }
    return Maybe<std::string>::Nothing();
}

Maybe<std::string> AppFactory::GetHomePage(const std::string& name) {
    for (const auto &a : apps) {
        if (a.className == name)
            return a.homePage;
    }
    return Maybe<std::string>::Nothing();
}