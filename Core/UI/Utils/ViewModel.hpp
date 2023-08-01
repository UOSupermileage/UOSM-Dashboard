//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_VIEWMODEL_HPP
#define UOSM_DASHBOARD_VIEWMODEL_HPP

#include <functional>

#include "DataAggregator.hpp"

/** @ingroup core-ui-utils
 *  A class that represents an abstract interface for a view model that provides data for a view.
 *  It holds a reference to a data aggregator that collects and processes the data from different sources.
 */
class ViewModel {
protected:
    /** The reference to the data aggregator that provides the data for the view model. */
    DataAggregator& aggregator;

    /** Constructs a view model with a given data aggregator.
     *  @param agg The reference to the data aggregator that provides the data for the view model.
     */
    explicit ViewModel(DataAggregator& agg) : aggregator(agg) {}

public:
    /** Returns a reference to the data aggregator that provides the data for the view model.
     *  @return A reference to the data aggregator that provides the data for the view model.
     */
    DataAggregator& GetAggregator() {
        return aggregator;
    }
};


#endif //UOSM_DASHBOARD_VIEWMODEL_HPP
