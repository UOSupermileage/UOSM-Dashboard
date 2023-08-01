//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_STATSVIEWMODEL_HPP
#define UOSM_DASHBOARD_STATSVIEWMODEL_HPP

#include "ViewModel.hpp"

/** @ingroup core-ui
 *  A class that represents a view model that provides data for the stats view.
 *  It inherits from the ViewModel class and uses the DataAggregator class to get the data from different sources.
 */
class StatsViewModel : public ViewModel {
public:
    /** Constructs a stats view model with a given data aggregator.
     *  @param aggregator The reference to the data aggregator that provides the data for the view model.
     */
    explicit StatsViewModel(DataAggregator& aggregator) : ViewModel(aggregator) {}
};


#endif //UOSM_DASHBOARD_STATSVIEWMODEL_HPP
