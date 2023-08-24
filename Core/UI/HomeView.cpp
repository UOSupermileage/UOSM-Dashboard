//
// Created by Jeremy Cote on 2023-07-28.
//

#include "HomeView.hpp"
#include "StylesManager.hpp"

HomeView::HomeView(lv_obj_t* parent, HomeViewModel& viewModel) : View(parent, viewModel), viewModel(viewModel) {
    Styles* styles = StylesManager::GetStyles();

    lv_obj_t* container = getContainer();
    lv_obj_add_style(container, styles->GetFullscreenViewStyle(), LV_PART_MAIN);

    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

    topRow = lv_obj_create(container);
    lv_obj_set_width(topRow, lv_obj_get_width(container));
    lv_obj_add_style(topRow, styles->GetFullscreenRowStyle(), LV_PART_MAIN);

    bottomRow = lv_obj_create(container);
    lv_obj_set_width(bottomRow, lv_obj_get_width(container));
    lv_obj_add_style(bottomRow, styles->GetFullscreenRowStyle(), LV_PART_MAIN);

    lv_obj_set_flex_grow(topRow, 1);
    lv_obj_set_flex_grow(bottomRow, 1);

    lapTimeLabel = lv_label_create(topRow);
    lv_label_set_text(lapTimeLabel, "0m 0s");
    lv_obj_add_style(lapTimeLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN);

    batteryVoltageLabel = lv_label_create(bottomRow);
    lv_label_set_text(batteryVoltageLabel, "0V");
    lv_obj_add_style(batteryVoltageLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN | LV_STATE_DEFAULT);

    motorRPMLabel = lv_label_create(bottomRow);
    lv_label_set_text(motorRPMLabel, "0 RPM");
    lv_obj_add_style(motorRPMLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN | LV_STATE_DEFAULT);

    lapTimeBarGraph = lv_chart_create(bottomRow);
    lv_chart_set_type(lapTimeBarGraph, LV_CHART_TYPE_BAR);
    lv_obj_set_size(lapTimeBarGraph, 200, 150);
    lv_obj_center(lapTimeBarGraph);
    lv_chart_set_range(lapTimeBarGraph, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_range(lapTimeBarGraph, LV_CHART_AXIS_SECONDARY_Y, 0, 400);
    lv_chart_set_point_count(lapTimeBarGraph, 12);

    /*Add ticks and label to every axis*/
    lv_chart_set_axis_tick(lapTimeBarGraph, LV_CHART_AXIS_PRIMARY_X, 10, 5, 12, 3, true, 40);
    lv_chart_set_axis_tick(lapTimeBarGraph, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 50);
    lv_chart_set_axis_tick(lapTimeBarGraph, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 3, 4, true, 50);

    /*Zoom in a little in X*/
    lv_chart_set_zoom_x(lapTimeBarGraph, 800);

    /*Add two data series*/
    lv_chart_series_t * ser1 = lv_chart_add_series(lapTimeBarGraph, lv_palette_lighten(LV_PALETTE_GREEN, 2), LV_CHART_AXIS_PRIMARY_Y);

    lv_coord_t * ser1_array = lv_chart_get_y_array(lapTimeBarGraph, ser1);
    /*Directly set points on 'ser2'*/

    lv_chart_set_next_value(lapTimeBarGraph , ser1, 31);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 66);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 89);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 63);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 56);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 32);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 35);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 57);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 85);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 22);
    lv_chart_set_next_value(lapTimeBarGraph, ser1, 58);

    /* ser1_array[0] = 92;
    ser1_array[1] = 71;
    ser1_array[2] = 61;
    ser1_array[3] = 15;
    ser1_array[4] = 21;
    ser1_array[5] = 35;
    ser1_array[6] = 35;
    ser1_array[7] = 58;
    ser1_array[8] = 31;
    ser1_array[9] = 53;
    ser1_array[10] = 33;
    ser1_array[11] = 73; */

    /* ser1_array = lapEfficiencies.GetValues(); */

    lv_chart_refresh(lapTimeBarGraph); /*Required after direct set*/


    viewModel.GetAggregator().batteryVoltage.addListener([this](const voltage_t& value) {
        uint32_t n = value * 33 * 185 / 40960;
        lv_label_set_text_fmt(batteryVoltageLabel, "%d.%d Volts", n / 10, n % 10);
    });

    viewModel.GetAggregator().motorRPM.addListener([this](const velocity_t& value) {
        lv_label_set_text_fmt(motorRPMLabel, "%d RPM", value);
    });

    viewModel.GetAggregator().lapTime.addListener([this](const ms_t& value) {
        lv_label_set_text_fmt(lapTimeLabel, "%dm %ds", value / 60000, value / 1000);
    });

    viewModel.GetAggregator().lapEfficiencies.addListener([this, ser1](const BarDataCollection<watt_hour_t> &value) {
        lv_chart_set_next_value(lapTimeBarGraph , ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_set_next_value(lapTimeBarGraph, ser1, 10);
        lv_chart_refresh(lapTimeBarGraph);
            });

}
