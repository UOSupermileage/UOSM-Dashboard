//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_HOMEVIEW_HPP
#define UOSM_DASHBOARD_HOMEVIEW_HPP

#include "View.hpp"
#include "HomeViewModel.hpp"

class HomeView : public View {
private:
    HomeViewModel* viewModel;

    lv_obj_t* batteryVoltageLabel;
    lv_obj_t* motorRPMLabel;

protected:
    ~HomeView() = default;

public:
    HomeView(lv_obj_t* parent, HomeViewModel* viewModel);
};


#endif //UOSM_DASHBOARD_HOMEVIEW_HPP
