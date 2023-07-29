//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_VIEWMODEL_HPP
#define UOSM_DASHBOARD_VIEWMODEL_HPP

#include <functional>

#include "DataAggregator.hpp"

class ViewModel {
protected:
    DataAggregator& aggregator;

    explicit ViewModel(DataAggregator& agg) : aggregator(agg) {}

public:
    DataAggregator& GetAggregator() {
        return aggregator;
    }
};


#endif //UOSM_DASHBOARD_VIEWMODEL_HPP
