//
// Created by Jeremy Cote on 2023-07-28.
// Modified by Annique Granchelli on 2024-01-29
//

#ifndef UOSM_DASHBOARD_HOMEVIEW_HPP
#define UOSM_DASHBOARD_HOMEVIEW_HPP

#include "View.hpp"

/** @ingroup core-ui
 *  A class that represents a view that displays the home screen of the dashboard.
 *  It inherits from the View class.
 */
class HomeView : public View {
private:
    /** Bottom row of the 2 row flex layout */
    lv_obj_t* topRow;
    lv_obj_t* bottomRow;

protected:
    /** Destructs the home view. */
    ~HomeView() = default;

public:
    /** Constructs a home view with a given parent and a home view model.
     *  @param parent The parent object of the container, or NULL if the container is a screen.
     *  @param aggregator The reference to the data aggregator to use as source of truth for this view.
     */
    HomeView(lv_obj_t* parent, DataAggregator& aggregator);
};


#endif //UOSM_DASHBOARD_HOMEVIEW_HPP
