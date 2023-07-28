//
// Created by Jeremy Cote on 2023-07-25.
//

#include "application.hpp"

#include "lvgl/lvgl.h"

#include "styles.hpp"

#include "home.hpp"

static void Application_Fetch_Data(lv_timer_t*);

static HomeViewModel* homeViewModel;
static lv_obj_t* homeView;

static lv_timer_t* dataTimer;

void Application_Create(void) {
    DebugPrint("Creating application");

    Styles_Init();

    homeViewModel = Home_CreateViewModel();

    // Create an object with no parent. (This will act as the screen).
    homeView = Home_CreateView(nullptr, homeViewModel);
    lv_scr_load(homeView);
}