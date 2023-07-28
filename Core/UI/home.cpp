//
// Created by Jeremy Cote on 2023-07-27.
//

#include "home.hpp"
#include "DataAggregationModule.h"
#include <cstdlib>

extern lv_style_t extraLargeTextStyle;

static lv_obj_t* batteryVoltageLabel;
static lv_obj_t* motorRPMLabel;

static lv_timer_t* dataTimer;

static void FetchData(lv_timer_t* timer);

lv_obj_t* Home_CreateView(lv_obj_t* parent, HomeViewModel* model) {
    lv_obj_t* container = lv_obj_create(parent);

    batteryVoltageLabel = lv_label_create(container);
    lv_label_set_text(batteryVoltageLabel, "0V");
    lv_obj_add_style(batteryVoltageLabel, &extraLargeTextStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    motorRPMLabel = lv_label_create(container);
    lv_label_set_text(motorRPMLabel, "0 RPM");
    lv_obj_add_style(motorRPMLabel, &extraLargeTextStyle, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_y(motorRPMLabel, 200);

    dataTimer = lv_timer_create(FetchData, HOME_DATA_REFRESH_RATE, nullptr);

    return container;
}


static void FetchData(lv_timer_t* timer) {
    DebugPrint("Fetching data");
    voltage_t voltage = SystemGetBatteryVoltage();
    uint32_t n = voltage * 33 * 185 / 40960;
    lv_label_set_text_fmt(batteryVoltageLabel, "%d.%d Volts", n / 10, n % 10);

    velocity_t velocity = SystemGetMotorRPM();
    lv_label_set_text_fmt(motorRPMLabel, "%d RPM", velocity);
}

HomeViewModel* Home_CreateViewModel() {
    auto* viewModel = (HomeViewModel*) malloc(sizeof(HomeViewModel));
    return viewModel;
}
