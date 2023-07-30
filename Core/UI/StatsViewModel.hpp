//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_STATSVIEWMODEL_HPP
#define UOSM_DASHBOARD_STATSVIEWMODEL_HPP

#include "ViewModel.hpp"

class StatsViewModel : public ViewModel {
public:
    explicit StatsViewModel(DataAggregator& aggregator) : ViewModel(aggregator) {}
};


#endif //UOSM_DASHBOARD_STATSVIEWMODEL_HPP
