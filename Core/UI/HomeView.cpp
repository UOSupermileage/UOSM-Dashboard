//
// Created by Jeremy Cote on 2023-07-28.
// Edited by Annique Granchelli on 2024-01-29
//

#include "HomeView.hpp"

#include <src/misc/lv_event_private.h>

#include "Utils/Cards.h"

#define MAX_SPEED 45

DualCardInfo HomeView::speedCards = DualCardInfo();
DualCardInfo HomeView::lapCards = DualCardInfo();
DualCardInfo HomeView::efficiencyCards = DualCardInfo();
DualCardInfo HomeView::consomationCards = DualCardInfo();

static lv_obj_t *l;
static void set_value(lv_obj_t * obj, int32_t v)
{
    static char buf[16];  // Buffer for formatted text
    snprintf(buf, sizeof(buf), "%d", v);
    lv_label_set_text(obj, buf);
}

// event callback
int v = 0;
static void event_handler(lv_event_t event)
{
    v++;
    set_value(HomeView::speedCards.get_card2()->get_value_label(), v);
}

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

    l = speedCards.get_card2()->get_value_label();

    lapCards = create_lap_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    obj = lapCards.get_dualCard();
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 2, 1,
    LV_GRID_ALIGN_STRETCH, 0, 1);
    // lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
    lv_obj_add_event_cb(obj, lv_event_cb_t(event_handler), LV_EVENT_SCROLL, NULL);

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
        set_value(speedCards.get_card2()->get_value_label(), speed);
    });

    aggregator.efficiency.addListener([&](lap_efficiencies_t efficiency) {
        set_value(efficiencyCards.get_card2()->get_value_label(), efficiency.all);
    });

    aggregator.batteryVoltage.addListener([&](voltage_t voltage) {
        set_value(consomationCards.get_card1()->get_value_label(), voltage);
    });

    aggregator.rpmSpeed.addListener([&](int32_t rpm) {
        set_value(speedCards.get_card2()->get_value_label(), rpm);
    });
}
