//
// Created by Jeremy Cote on 2023-07-27.
//

#ifndef UOSM_DASHBOARD_HOMEVIEWMODEL_HPP
#define UOSM_DASHBOARD_HOMEVIEWMODEL_HPP

#include "ApplicationTypes.h"
#include "lvgl/lvgl.h"
#include "ViewModel.hpp"
#include "DataAggregator.hpp"

class HomeViewModel : public ViewModel {
public:
    explicit HomeViewModel(DataAggregator& aggregator) : ViewModel(aggregator) {}
};

#endif //UOSM_DASHBOARD_HOMEVIEWMODEL_HPP
