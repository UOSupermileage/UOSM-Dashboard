//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_STATSVIEW_HPP
#define UOSM_DASHBOARD_STATSVIEW_HPP

#include "View.hpp"
#include "StatsViewModel.hpp"
#include "CombineLatest.hpp"

/** @ingroup core-ui
 *  A class that represents a view that displays the statistics of the dashboard, such as the motor RPM over time.
 *  It inherits from the View class and uses the StatsViewModel class to get the data for the view elements.
 */
class StatsView : public View {
private:
    /** The reference to the stats view model that provides the data for the view elements. */
    StatsViewModel& viewModel;

    /** The chart that displays the motor RPM over time. */
    lv_obj_t* chart;
    /** The series that represents the motor RPM data. */
    lv_chart_series_t* rpmSeries;
    /** The label that displays the current motor RPM. */
    lv_obj_t* rpmLabel;

    /** Combiner to get latest value from multiple observed objects whenever one of them changes */
    CombineLatest<velocity_t, voltage_t>* combiner;

protected:
    /** Destructs the stats view. */
    ~StatsView();

public:
    /** Constructs a stats view with a given parent and a stats view model.
     *  @param parent The parent object of the container, or NULL if the container is a screen.
     *  @param viewModel The reference to the stats view model that provides the data for the view elements.
     */
    StatsView(lv_obj_t* parent, StatsViewModel& viewModel);
};


#endif //UOSM_DASHBOARD_STATSVIEW_HPP
