//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_STATSVIEW_HPP
#define UOSM_DASHBOARD_STATSVIEW_HPP

#include "View.hpp"
#include "CombineLatest.hpp"

/** @ingroup core-ui
 *  A class that represents a view that displays the statistics of the dashboard, such as the motor RPM over time.
 *  It inherits from the View class.
 */
class StatsView : public View {
private:
    /** The chart that displays the motor RPM over time. */
    lv_obj_t* chart;
    /** The series that represents the motor RPM data. */
    lv_chart_series_t* rpmSeries;
    /** The label that displays the current motor RPM. */
    lv_obj_t* rpmLabel;

    /** Combiner to get latest value from multiple observed objects whenever one of them changes */
    CombineLatest<DataQueue<velocity_t>, DataQueue<voltage_t>>* combiner;

protected:
    /** Destructs the stats view. */
    ~StatsView();

public:
    /** Constructs a stats view with a given parent and a stats view model.
     *  @param parent The parent object of the container, or NULL if the container is a screen.
     *  @param aggregator The reference to the data aggregator to use as source of truth for this view.
     */
    StatsView(lv_obj_t* parent, DataAggregator& aggregator);
};


#endif //UOSM_DASHBOARD_STATSVIEW_HPP
