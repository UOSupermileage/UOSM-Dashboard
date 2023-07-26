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

static lv_obj_t* rpmLabel;

static lv_timer_t* dataTimer;

void Application_Create(void) {
    DebugPrint("Creating application");

    // Create an object with no parent. (This will act as the screen).
    homeScreen = lv_obj_create(NULL);
    lv_scr_load(homeScreen);

    lv_style_init(&extraLargeTextStyle);
    lv_style_set_text_font(&extraLargeTextStyle, &lv_font_montserrat_48);

    rpmLabel = lv_label_create(homeScreen);
    lv_label_set_text(rpmLabel, "3000 RPM");
    lv_obj_add_style(rpmLabel, &extraLargeTextStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    dataTimer = lv_timer_create(Application_Fetch_Data, 250, NULL);
}

static void Application_Fetch_Data(lv_timer_t* timer) {
    DebugPrint("Fetching data");
    velocity_t rpm = SystemGetMotorRPM();
    lv_label_set_text_fmt(rpmLabel, "%d RPM", rpm);
}