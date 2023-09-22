//
// Created by Jeremy Cote on 2023-07-28.
//

#include "HomeView.hpp"
#include "StylesManager.hpp"

lv_obj_t * ai;
lv_obj_t * notAi;

static void setArcValue(lv_obj_t * arc, int value) {
    lv_arc_set_value(arc, value);
}

HomeView::HomeView(lv_obj_t* parent, HomeViewModel& viewModel) : View(parent, viewModel), viewModel(viewModel) {
    Styles* styles = StylesManager::GetStyles();

    lv_obj_t* container = getContainer();
    lv_obj_add_style(container, styles->GetFullscreenViewStyle(), LV_PART_MAIN);

    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

//    topRow = lv_obj_create(container);
//    lv_obj_set_width(topRow, lv_obj_get_width(container));
//    lv_obj_add_style(topRow, styles->GetFullscreenRowStyle(), LV_PART_MAIN);

    bottomRow = lv_obj_create(container);
    lv_obj_set_width(bottomRow, lv_obj_get_width(container));
    lv_obj_add_style(bottomRow, styles->GetFullscreenRowStyle(), LV_PART_MAIN);

//    lv_obj_set_flex_grow(topRow, 1);
    lv_obj_set_flex_grow(bottomRow, 1);

    lapTimeLabel = lv_label_create(bottomRow);
    lv_label_set_text(lapTimeLabel, "0m 0s");
    lv_obj_add_style(lapTimeLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN);

    batteryVoltageLabel = lv_label_create(bottomRow);
    lv_label_set_text(batteryVoltageLabel, "0V");
    lv_obj_add_style(batteryVoltageLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(batteryVoltageLabel);
    lv_obj_align(batteryVoltageLabel, LV_ALIGN_BOTTOM_MID, 0, 0);

//    motorRPMLabel = lv_label_create(bottomRow);
//    lv_label_set_text(motorRPMLabel, "0 RPM");
//    lv_obj_add_style(motorRPMLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN | LV_STATE_DEFAULT);

    aiThrottleArc = lv_arc_create(bottomRow);
    lv_arc_set_bg_angles(aiThrottleArc, 0, 270);
    lv_arc_set_angles(aiThrottleArc, 0, 0);
    lv_arc_set_rotation(aiThrottleArc, 135);
    lv_obj_set_size(aiThrottleArc, 475, 475);
    lv_obj_center(aiThrottleArc);
    lv_obj_clear_flag(aiThrottleArc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_style(aiThrottleArc, NULL, LV_PART_KNOB);
    lv_obj_add_style(aiThrottleArc, styles->GetMainArcStyle(), LV_PART_MAIN);
    lv_obj_add_style(aiThrottleArc, styles->GetAiThrottleArcStyle(), LV_PART_INDICATOR);
    lv_arc_set_value(aiThrottleArc, 50);

    throttleArc = lv_arc_create(bottomRow);
    lv_arc_set_bg_angles(throttleArc, 0, 270);
    lv_arc_set_angles(throttleArc, 0, 0);
    lv_arc_set_rotation(throttleArc, 135);
    lv_obj_set_size(throttleArc, 375, 375);
    lv_obj_center(throttleArc);
    lv_obj_clear_flag(throttleArc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_style(throttleArc, NULL, LV_PART_KNOB);
    lv_obj_add_style(throttleArc, styles->GetMainArcStyle(), LV_PART_MAIN);
    lv_obj_add_style(throttleArc, styles->GetThrottleArcStyle(), LV_PART_INDICATOR);
    lv_arc_set_value(throttleArc, 50);

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

//    viewModel.GetAggregator().motorVelocities.addListenerForLatest([this](const velocity_t& velocity) {
//        lv_label_set_text_fmt(motorRPMLabel, "%d RPM", velocity);
//    });

    viewModel.GetAggregator().lapTimes.addListenerForLatest([this](const ms_t& time) {
        lv_label_set_text_fmt(lapTimeLabel, "%dm %ds", time / 60000, time / 1000);
    });

    viewModel.GetAggregator().lapTimes.addListener([this](const DataQueue<ms_t>& queue) {
        lv_chart_set_point_count(lapTimeBarGraph, queue.getNumberOfElements());
        lv_chart_refresh(lapTimeBarGraph);
    });

    viewModel.GetAggregator().throttlePositions.addListenerForLatest([this](const throttle_raw_t& throttle) {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, throttleArc);
        lv_anim_set_exec_cb(&a, reinterpret_cast<lv_anim_exec_xcb_t>(setArcValue));
        lv_anim_set_time(&a, 100);
        lv_anim_set_values(&a, lv_arc_get_value(throttleArc), throttle);
        lv_anim_start(&a);
    });

    ai = aiThrottleArc;
    notAi = throttleArc;

    lv_timer_t * timer = lv_timer_create([](lv_timer_t * timer) {lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, ai);
        lv_anim_set_exec_cb(&a, reinterpret_cast<lv_anim_exec_xcb_t>(setArcValue));
        lv_anim_set_time(&a, 100);
        lv_anim_set_values(&a, lv_arc_get_value(ai), 10+rand()%80);
        lv_anim_start(&a);
    }, 500, nullptr);
}
