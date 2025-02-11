//
// Created by Jeremy Cote on 2023-07-28.
// Edited by Annique Granchelli on 2024-01-29
//

#include "HomeView.hpp"

#include <src/misc/lv_event_private.h>

#include "Utils/Cards.h"
// add font
// LV_FONT_DECLARE(montserrat_72);

#define MAX_SPEED 45
static lv_obj_t *l;
static void set_value(lv_obj_t * obj, int32_t v)
{
    static char buf[16];  // Buffer for formatted text
    snprintf(buf, sizeof(buf), "%d", v);
    lv_label_set_text(obj, buf);
}

static void event_cb(lv_event_t * e)
{
    static int32_t idk = 0;
    set_value(l, ++idk);
}



DualCardInfo speedCards;
DualCardInfo lapCards;
DualCardInfo efficiencyCards;
DualCardInfo consomationCards;

// static void event_cb(lv_event_t * e)
// {
//     DebugPrint("AAAAAA");
//     set_value(speedCards.get_card2()->get_value_label(), ++idk);
// }
// get card
// ---------------------
// Title
//        Value
// ---------------------

// lv_obj_t * create_dual_card_info(lv_obj_t * parent, const char * title1, const char * value1, const char * title2, const char * value2, const int32_t width, const int32_t height) {
//
//
//     return cont;
// }

// speed section
// ---------------------
// Speed
//        45
// ---------------------
// RPM

//        5000

// ---------------------
DualCardInfo create_speed_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    return DualCardInfo(parent, "Speed", "45", "RPM", "5000", width, height);
}

DualCardInfo create_lap_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    return DualCardInfo(parent, "Current Lap", "03:05", "Last Lap", "05:34", width, height);
}

DualCardInfo create_efficienty_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    return DualCardInfo(parent, "Efficiency", "20.5", "Suggestion", "SLOWER", width, height);
}

DualCardInfo create_consomation_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    return DualCardInfo(parent, "Voltage", "10 V", "Current", "12 Amp", width, height);
}

// Function to update the label
// void update_label() {
//     static char buf[16];  // Buffer for formatted text
//     snprintf(buf, sizeof(buf), "Value: %d", counter);
//     lv_label_set_text(label, buf);
// }
//
// void update_label(lv_obj_t * label) {
//     static char buf[16];  // Buffer for formatted text
//     snprintf(buf, sizeof(buf), "Value: %d", counter);
//     lv_label_set_text(label, buf);
// }

HomeView::HomeView(lv_obj_t* parent, DataAggregator& aggregator) : View(parent, aggregator) {
//
//     // Create a label
//     label = lv_label_create(getContainer());
//     lv_label_set_text(label, "Value: 0");  // Initial value
//     lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);  // Center it on the screen
//
//     // Simulate updating the variable
//     lv_timer_create([](lv_timer_t *t) {
//         counter++;
//         update_label();
//     }, 1000, NULL);  // Update every second
// }

// void i(lv_obj_t * cont){
    // get resoltion of the screen
    lv_obj_t * cont = getContainer();

    DebugPrint("res : %d, %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);

    static int32_t col_dsc[] = {SCREEN_WIDTH/2 -1, 2, SCREEN_WIDTH/2 -1, LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {SCREEN_HEIGHT/2 -1, 2, SCREEN_HEIGHT/2 -1, LV_GRID_TEMPLATE_LAST};

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

    l = speedCards.get_card2()->get_value_label();

    lapCards = create_lap_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    obj = lapCards.get_dualCard();
    lv_obj_add_event_cb(obj, event_cb, LV_EVENT_SCROLL, nullptr);   /* Assign an event callback */
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1,
    LV_GRID_ALIGN_STRETCH, 0, 1);

    efficiencyCards = create_efficienty_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    obj = efficiencyCards.get_dualCard();
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
    LV_GRID_ALIGN_STRETCH, 2, 1);

    consomationCards = create_consomation_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    obj = consomationCards.get_dualCard();
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1,
                         LV_GRID_ALIGN_STRETCH, 2, 1);

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
}
