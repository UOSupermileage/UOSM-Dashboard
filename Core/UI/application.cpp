//
// Created by Jeremy Cote on 2023-07-25.
//

#include "application.h"

#include "lvgl/lvgl.h"

#include "DataAggregator.hpp"
#include "DataAggregatorWrapper.h"

#include "HomeView.hpp"

static HomeView* homeView;

void Application_Create(DataAggregatorWrapper* aggregatorWrapper) {
    DebugPrint("Creating application");

    if (aggregatorWrapper == nullptr) {
        DebugPrint("DataAggregatorWrapper is null, will not start application");
        return;
    }

    DataAggregator& aggregator = DataAggregator_GetReference(aggregatorWrapper);

    DebugPrint("Creating HomeView");

    DebugPrint("Aggregator: %04x", aggregatorWrapper);

    // Create an object with no parent. (This will act as the screen).
    homeView = new HomeView(nullptr, aggregator);

    DebugPrint("Setting Size");
    lv_obj_set_size(homeView->getContainer(), SCREEN_WIDTH, SCREEN_HEIGHT);

    DebugPrint("Loading View");
    lv_scr_load(homeView->getContainer());
}