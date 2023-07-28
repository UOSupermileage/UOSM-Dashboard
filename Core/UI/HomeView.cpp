//
// Created by Jeremy Cote on 2023-07-28.
//

#include "HomeView.hpp"
#include "StylesManager.hpp"

HomeView::HomeView(lv_obj_t* parent, HomeViewModel* viewModel) : View(parent) {
    this->viewModel = viewModel;

    lv_obj_t* container = GetContainer();

    Styles* styles = StylesManager::GetStyles();

    batteryVoltageLabel = lv_label_create(container);
    lv_label_set_text(batteryVoltageLabel, "0V");
    lv_obj_add_style(batteryVoltageLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN | LV_STATE_DEFAULT);

    motorRPMLabel = lv_label_create(container);
    lv_label_set_text(motorRPMLabel, "0 RPM");
    lv_obj_add_style(motorRPMLabel, styles->GetExtraLargeTextStyle(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_y(motorRPMLabel, 200);
}
