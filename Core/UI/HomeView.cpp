//
// Created by Jeremy Cote on 2023-07-28.
// Edited by Annique Granchelli on 2024-01-29
//

#include "HomeView.hpp"

#ifdef SIM
#include <src/misc/lv_event_private.h>
#endif

#include "Utils/Cards.h"
#include "Tasks/LVGLTimerTask.h"

#include <chrono>


#define MAX_SPEED 40
#define RED "#FF0000"
#define BLACK "#000000"
uint32_t lapTimer = 0;
uint8_t stopCounter = 0;
uint32_t lastRpm = 0;

DualCardInfo HomeView::speedCards = DualCardInfo();
DualCardInfo HomeView::lapCards = DualCardInfo();
DualCardInfo HomeView::efficiencyCards = DualCardInfo();
DualCardInfo HomeView::consomationCards = DualCardInfo();



static void set_value(lv_obj_t * obj, int32_t v)
{
    static char buf[16];  // Buffer for formatted text
    snprintf(buf, sizeof(buf), "%d", v);
    lv_label_set_text(obj, buf);
}

static void update_lap_time(lv_obj_t * obj) {
    uint32_t minutes = lapTimer / 60;
    uint32_t seconds = lapTimer % 60;

    static char buf[16];  // Buffer for formatted text
    snprintf(buf, sizeof(buf), "%02d:%02d", minutes, seconds);
    //DebugPrint(buf);
    lv_label_set_text(obj, buf);
}

static void reset_lap_timer() {
    lapTimer = 0;
    //DebugPrint("Lap timer reset\n");
    update_lap_time(HomeView::lapCards.get_card1()->get_value_label());
}

static void reset_lap_timer(lv_event_t * e) {
    reset_lap_timer();
}

static void set_speed(lv_obj_t * obj, int32_t v)
{
    static char buf[16];  // Buffer for formatted text
    v = v/1000;
    lv_label_set_recolor(obj,true);

    if (v >= MAX_SPEED) {
        snprintf(buf, sizeof(buf), "%s %d km/h #",RED, v);
    } else {
        snprintf(buf, sizeof(buf), "%s %d km/h #",BLACK, v);
    }

    lv_label_set_text(obj, buf);
}

static void set_current(lv_obj_t * obj, int32_t v)
{
    static char buf[16];  // Buffer for formatted text
    snprintf(buf, sizeof(buf), "%d Amp", v);
    lv_label_set_text(obj, buf);
}

// event callback
// int v = 0;
// static void event_handler(lv_event_t event)
// {
//     v++;
//     set_value(HomeView::speedCards.get_card2()->get_value_label(), v);
// }

DualCardInfo create_speed_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    return DualCardInfo(parent, "Speed", "000", "RPM", "0", width, height);
}

DualCardInfo create_lap_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    return DualCardInfo(parent, "Current Lap", "00:00", "Temp (Celsius)", "0", width, height);
    

}

DualCardInfo create_efficienty_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    return DualCardInfo(parent, "Efficiency", "0", "Suggestion", "SLOWER", width, height);
}

DualCardInfo create_consomation_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    return DualCardInfo(parent, "Voltage", "0", "Current", "0", width, height);
}

HomeView::HomeView(lv_obj_t* parent, DataAggregator& aggregator) : View(parent, aggregator) {
    // get resoltion of the screen
    lv_obj_t * cont = getContainer();

    DebugPrint("res : %d, %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);

    static lv_coord_t col_dsc[] = {SCREEN_WIDTH/2 -1, 2, SCREEN_WIDTH/2 -1, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {SCREEN_HEIGHT/2 -1, 2, SCREEN_HEIGHT/2 -1, LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    // lv_obj_t * cont = lv_obj_create(lv_screen_active());
    // lv_obj_t * cont = parent;
    lv_obj_set_grid_align(cont, LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_END);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    // lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    // lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_center(cont);
    // lv_obj_set_layout(cont, LV_LAYOUT_GRID);

    lv_obj_t * obj;

    // obj = lv_button_create(cont);
    speedCards = create_speed_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    obj = speedCards.get_dualCard();
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
    LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
    lapCards = create_lap_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    obj = lapCards.get_dualCard();
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1,
    LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
    // lv_obj_add_event_cb(obj, lv_event_cb_t(event_handler), LV_EVENT_SCROLL, NULL);
    // lv_obj_add_event_cb(obj, reset_lap_timer, LV_EVENT_CLICKED, NULL);

    efficiencyCards = create_efficienty_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    obj = efficiencyCards.get_dualCard();
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
    LV_GRID_ALIGN_STRETCH, 2, 1);
    lv_obj_set_scroll_dir(obj, LV_DIR_NONE);

    consomationCards = create_consomation_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    obj = consomationCards.get_dualCard();
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1,
                         LV_GRID_ALIGN_STRETCH, 2, 1);
    lv_obj_set_scroll_dir(obj, LV_DIR_NONE);

    // add vertical separator
    lv_obj_t * separator = lv_obj_create(cont);
    lv_obj_set_size(separator, 2, SCREEN_HEIGHT);
    lv_obj_set_style_bg_color(separator, lv_color_hex(0x000000), 0);
    lv_obj_set_grid_cell(separator, LV_GRID_ALIGN_CENTER, 1, 1,
                         LV_GRID_ALIGN_CENTER, 0, 3);

    // add horizontal separator
    lv_obj_t * separator2 = lv_obj_create(cont);
    lv_obj_set_size(separator2, SCREEN_WIDTH, 2);
    lv_obj_set_style_bg_color(separator2, lv_color_hex(0x000000), 0);
    lv_obj_set_grid_cell(separator2, LV_GRID_ALIGN_CENTER, 0, 3,
                         LV_GRID_ALIGN_CENTER, 1, 1);

    lv_obj_set_style_pad_column(cont, 0, 0);
    lv_obj_set_style_pad_row(cont, 0, 0);

    aggregator.speed.addListener([&](speed_t speed) {
        LVGL_Lock();
        set_speed(speedCards.get_card1()->get_value_label(), speed);
        LVGL_Unlock();
    });

    aggregator.efficiency.addListener([&](lap_efficiencies_t efficiency) {
        LVGL_Lock();
        set_value(efficiencyCards.get_card2()->get_value_label(), efficiency.lap_0);
        LVGL_Unlock();
    });

    aggregator.batteryVoltage.addListener([&](voltage_t voltage) {
        LVGL_Lock();
        set_value(consomationCards.get_card1()->get_value_label(), voltage);
        LVGL_Unlock();
    });

    aggregator.batteryCurrent.addListener([&](current_t current) {
        LVGL_Lock();
        set_current(consomationCards.get_card2()->get_value_label(), current);
        LVGL_Unlock();
    });

    aggregator.rpmSpeed.addListener([&](int32_t rpm) {
        // if (rpm == 0 && lastRpm != 0) {
        //     stopCounter++;
        //     if (stopCounter >= 2) {
        //         reset_lap_timer();
        //         stopCounter = 0;
        //     }
        // }
        LVGL_Lock();
        set_value(speedCards.get_card2()->get_value_label(), rpm);
        LVGL_Unlock();
    });

    aggregator.temperature.addListener([&](temperature_t temperature) {
        LVGL_Lock();
        set_value(lapCards.get_card2()->get_value_label(), temperature);
        LVGL_Unlock();
    });

    aggregator.lapTimer.addListener([&](uint32_t timer) {
        LVGL_Lock();
        lapTimer = timer;
        update_lap_time(lapCards.get_card1()->get_value_label());
        LVGL_Unlock();
    });

    __attribute__ ((__unused__)) lv_timer_t * timer = lv_timer_create([](lv_timer_t * timer) {
        lapTimer++;
        update_lap_time(lapCards.get_card1()->get_value_label());
    }, 1000, NULL);
}
