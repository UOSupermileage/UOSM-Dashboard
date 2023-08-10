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
}
