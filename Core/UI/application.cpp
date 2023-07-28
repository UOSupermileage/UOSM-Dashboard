//
// Created by Jeremy Cote on 2023-07-25.
//

#include "application.h"

#include "lvgl/lvgl.h"

#include "Styles.hpp"

#include "HomeView.hpp"
#include "HomeViewModel.hpp"

static void Application_Fetch_Data(lv_timer_t*);

static HomeViewModel* homeViewModel;
static HomeView* homeView;

static lv_timer_t* dataTimer;

void Application_Create(void) {
    DebugPrint("Creating application");

    homeViewModel = new HomeViewModel();

    // Create an object with no parent. (This will act as the screen).
    homeView = new HomeView(nullptr, homeViewModel);
    lv_scr_load(homeView->GetContainer());
}