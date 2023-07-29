//
// Created by Jeremy Cote on 2023-07-25.
//

#include "application.h"

#include "lvgl/lvgl.h"

#include "DataAggregator.hpp"
#include "DataAggregatorWrapper.h"

#include "HomeView.hpp"
#include "HomeViewModel.hpp"

static void Application_Fetch_Data(lv_timer_t*);

static HomeViewModel* homeViewModel;
static HomeView* homeView;

static lv_timer_t* dataTimer;

void Application_Create(DataAggregatorWrapper* aggregatorWrapper) {
    DebugPrint("Creating application");

    if (aggregatorWrapper == nullptr) {
        DebugPrint("DataAggregatorWrapper is null, will not start application");
        return;
    }

    DataAggregator& aggregator = DataAggregator_GetReference(aggregatorWrapper);

    homeViewModel = new HomeViewModel(aggregator);

    // Create an object with no parent. (This will act as the screen).
    homeView = new HomeView(nullptr, *homeViewModel);
    lv_scr_load(homeView->getContainer());
}