//
// Created by Jeremy Cote on 2023-07-27.
//

#ifndef UOSM_DASHBOARD_HOMEVIEWMODEL_HPP
#define UOSM_DASHBOARD_HOMEVIEWMODEL_HPP

#include "ApplicationTypes.h"
#include "lvgl/lvgl.h"
#include "ViewModel.hpp"
#include "DataAggregator.hpp"

/** @ingroup core-ui
 *  A class that represents a view model that provides data for the home view.
 *  It inherits from the ViewModel class and uses the DataAggregator class to get the data from different sources.
 */
class HomeViewModel : public ViewModel {
public:
    explicit HomeViewModel(DataAggregator& aggregator) : ViewModel(aggregator) {

    }
};

#endif //UOSM_DASHBOARD_HOMEVIEWMODEL_HPP
