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
    lv_chart_set_range(lapTimeBarGraph, LV_CHART_AXIS_PRIMARY_Y, 0, 1010);
    lv_chart_set_range(lapTimeBarGraph, LV_CHART_AXIS_SECONDARY_Y, 0, 1010);
//    lv_chart_set_point_count(lapTimeBarGraph, 12);

    /*Add ticks and label to every axis*/
    lv_chart_set_axis_tick(lapTimeBarGraph, LV_CHART_AXIS_PRIMARY_X, 10, 5, 12, 3, true, 40);
    lv_chart_set_axis_tick(lapTimeBarGraph, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 50);
    lv_chart_set_axis_tick(lapTimeBarGraph, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 3, 4, true, 50);

    /*Zoom in a little in X*/
//    lv_chart_set_zoom_x(lapTimeBarGraph, 800);

    /*Add two data series*/
    lv_chart_series_t * ser1 = lv_chart_add_series(lapTimeBarGraph, lv_palette_lighten(LV_PALETTE_GREEN, 2), LV_CHART_AXIS_PRIMARY_Y);

    lv_chart_set_point_count(lapTimeBarGraph, viewModel.GetAggregator().lapTimes.getNumberOfElements());
    lv_chart_set_ext_y_array(lapTimeBarGraph, ser1,
                             reinterpret_cast<lv_coord_t *>(viewModel.GetAggregator().lapTimes.getValues()));
    lv_chart_refresh(lapTimeBarGraph); /*Required after direct set*/

    viewModel.GetAggregator().batteryVoltages.addListenerForLatest([this](const voltage_t& voltage) {
        uint32_t n = voltage * 33 * 185 / 40960;
        lv_label_set_text_fmt(batteryVoltageLabel, "%d.%d Volts", n / 10, n % 10);
    });

    viewModel.GetAggregator().motorVelocities.addListenerForLatest([this](const velocity_t& velocity) {
        lv_label_set_text_fmt(motorRPMLabel, "%d RPM", velocity);
    });

    viewModel.GetAggregator().lapTimes.addListenerForLatest([this](const ms_t& time) {
        lv_label_set_text_fmt(lapTimeLabel, "%dm %ds", time / 60000, time / 1000);
    });

    viewModel.GetAggregator().lapTimes.addListener([this](const DataQueue<ms_t>& queue) {
        lv_chart_set_point_count(lapTimeBarGraph, queue.getNumberOfElements());
        lv_chart_refresh(lapTimeBarGraph);
    });
}
