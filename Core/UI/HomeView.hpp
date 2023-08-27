//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_HOMEVIEW_HPP
#define UOSM_DASHBOARD_HOMEVIEW_HPP

#include "View.hpp"
#include "HomeViewModel.hpp"

/** @ingroup core-ui
 *  A class that represents a view that displays the home screen of the dashboard.
 *  It inherits from the View class and uses the \ref HomeViewModel class to get the data for the view elements.
 */
class HomeView : public View {
private:
    /** The reference to the home view model that provides the data for the view elements. */
    HomeViewModel& viewModel;

    /** The label that displays the current lap time. */
    lv_obj_t* lapTimeLabel;

    /** The label that displays the battery voltage. */
    lv_obj_t* batteryVoltageLabel;
    /** The label that displays the motor RPM. */
    lv_obj_t* motorRPMLabel;

    /** bar graph for time laps display. */
    lv_obj_t* lapTimeBarGraph;

    /** Top row of the 2 row flex layout */
    lv_obj_t* topRow;

    /** Bottom row of the 2 row flex layout */
    lv_obj_t* bottomRow;

protected:
    /** Destructs the home view. */
    ~HomeView() = default;

public:
    /** Constructs a home view with a given parent and a home view model.
     *  @param parent The parent object of the container, or NULL if the container is a screen.
     *  @param viewModel The reference to the home view model that provides the data for the view elements.
     */
    HomeView(lv_obj_t* parent, HomeViewModel& viewModel);
};


#endif //UOSM_DASHBOARD_HOMEVIEW_HPP
