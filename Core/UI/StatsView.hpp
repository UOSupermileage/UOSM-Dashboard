//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_STATSVIEW_HPP
#define UOSM_DASHBOARD_STATSVIEW_HPP

#include "View.hpp"
#include "StatsViewModel.hpp"

class StatsView : public View {
private:
    StatsViewModel& viewModel;
    
    lv_obj_t* batteryVoltageLabel;

protected:
    ~StatsView() = default;

public:
    StatsView(lv_obj_t* parent, StatsViewModel& viewModel);
};


#endif //UOSM_DASHBOARD_STATSVIEW_HPP