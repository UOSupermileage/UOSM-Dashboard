//
// Created by Jeremy Cote on 2023-07-25.
//

#include "application.h"

#include "lvgl/lvgl.h"

#include "Constants.h"

#include "DataAggregator.hpp"
#include "DataAggregatorWrapper.h"

#include "HomeView.hpp"

static HomeView* homeView;

static uint8_t screenIndex = 0;
static uint8_t nScreens = 3;

void swipe_event_callback(lv_event_t* event) {
    if (event->code == LV_EVENT_GESTURE) {
        lv_dir_t direction = lv_indev_get_gesture_dir(lv_indev_get_act());

        if (direction == LV_DIR_LEFT) {

            if (screenIndex == 0) {
                screenIndex = nScreens - 1;
            } else {
                screenIndex--;
            }
        } else if (direction == LV_DIR_RIGHT) {
            screenIndex++;
            screenIndex = screenIndex % nScreens;
        } else {
            return;
        }
    }
}

void Application_Create(DataAggregatorWrapper* aggregatorWrapper) {
    DebugPrint("Creating application");

    if (aggregatorWrapper == nullptr) {
        DebugPrint("DataAggregatorWrapper is null, will not start application");
        return;
    }

    DataAggregator& aggregator = DataAggregator_GetReference(aggregatorWrapper);

    // Create an object with no parent. (This will act as the screen).
    homeView = new HomeView(nullptr, aggregator);
    lv_obj_set_size(homeView->getContainer(), SCREEN_WIDTH, SCREEN_HEIGHT);

    lv_scr_load(homeView->getContainer());
}