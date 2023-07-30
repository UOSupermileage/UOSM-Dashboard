//
// Created by Jeremy Cote on 2023-07-29.
//

#include "StatsView.hpp"
#include "StylesManager.hpp"

StatsView::StatsView(lv_obj_t* parent, StatsViewModel& viewModel) : View(parent, viewModel), viewModel(viewModel) {
    lv_obj_t* container = getContainer();

    Styles* styles = StylesManager::GetStyles();

    batteryVoltageLabel = lv_label_create(container);
    lv_label_set_text(batteryVoltageLabel, "0V");
    lv_obj_add_style(batteryVoltageLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN | LV_STATE_DEFAULT);
}