//
// Created by Jeremy Cote on 2023-07-25.
//

#include "application.h"

#include "lvgl/lvgl.h"
#include "DataAggregationModule.h"

static void Application_Fetch_Data(lv_timer_t*);

static lv_style_t extraLargeTextStyle;

static lv_obj_t* homeScreen;
static lv_obj_t* statsScreen;

static lv_obj_t* batteryVoltageLabel;
static lv_obj_t* motorRPMLabel;

static lv_timer_t* dataTimer;

void Application_Create(void) {
    DebugPrint("Creating application");

    // Create an object with no parent. (This will act as the screen).
    homeScreen = lv_obj_create(NULL);
    lv_scr_load(homeScreen);

    lv_style_init(&extraLargeTextStyle);
    lv_style_set_text_font(&extraLargeTextStyle, &lv_font_montserrat_48);

    batteryVoltageLabel = lv_label_create(homeScreen);
    lv_label_set_text(batteryVoltageLabel, "0V");
    lv_obj_add_style(batteryVoltageLabel, &extraLargeTextStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    motorRPMLabel = lv_label_create(homeScreen);
    lv_label_set_text(motorRPMLabel, "0 RPM");
    lv_obj_add_style(motorRPMLabel, &extraLargeTextStyle, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_y(motorRPMLabel, 200);

    dataTimer = lv_timer_create(Application_Fetch_Data, 250, NULL);
}

static void Application_Fetch_Data(lv_timer_t* timer) {
    DebugPrint("Fetching data");
    voltage_t voltage = SystemGetBatteryVoltage();
    uint32_t n = voltage * 33 * 185 / 40960;
    lv_label_set_text_fmt(batteryVoltageLabel, "%d.%d Volts", n / 10, n % 10);

    velocity_t velocity = SystemGetMotorRPM();
    lv_label_set_text_fmt(motorRPMLabel, "%d RPM", velocity);
}