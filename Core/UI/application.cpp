//
// Created by Jeremy Cote on 2023-07-25.
//

#include "application.h"

#include "lvgl/lvgl.h"

#include "Constants.h"

#include "DataAggregator.hpp"
#include "DataAggregatorWrapper.h"

#include "HomeView.hpp"
#include "StatsView.hpp"

static void Application_Fetch_Data(lv_timer_t*);

static HomeView* homeView;

static StatsView* statsView;

static lv_timer_t* dataTimer;

static uint8_t screenIndex = 0;
static uint8_t nScreens = 2;

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

        lv_scr_load_anim_t animDirection =
                direction == LV_DIR_LEFT ? LV_SCR_LOAD_ANIM_MOVE_LEFT : LV_SCR_LOAD_ANIM_MOVE_RIGHT;

        switch (screenIndex) {
            case 0:
                lv_scr_load_anim(homeView->getContainer(), animDirection, 300, 0, false);
                break;
            case 1:
                lv_scr_load_anim(statsView->getContainer(), animDirection, 300, 0, false);
                break;
            default:
                break;
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

    statsView = new StatsView(nullptr, aggregator);
    lv_obj_set_size(statsView->getContainer(), SCREEN_WIDTH, SCREEN_HEIGHT);

    lv_scr_load(homeView->getContainer());

    lv_obj_add_event_cb(homeView->getContainer(), swipe_event_callback, LV_EVENT_GESTURE, nullptr);
    lv_obj_add_event_cb(statsView->getContainer(), swipe_event_callback, LV_EVENT_GESTURE, nullptr);
}