//
// Created by Jeremy Cote on 2023-09-23.
//

#ifndef UOSM_DASHBOARD_SDL_LOGVIEW_HPP
#define UOSM_DASHBOARD_SDL_LOGVIEW_HPP


#include "View.hpp"

/** @ingroup core-ui
 *  A class that represents a view that displays the can log screen of the dashboard.
 *  It inherits from the View class.
 */
class LogView : public View {
private:
    /** The table that displays can logs. One row per message */
    lv_obj_t* table;

protected:
    /** Destructs the log view. */
    ~LogView() = default;

public:
    /** Constructs a log view with a given parent.
     *  @param parent The parent object of the container, or NULL if the container is a screen.
     *  @param aggregator The reference to the data aggregator to use as source of truth for this view.
     */
    LogView(lv_obj_t* parent, DataAggregator& aggregator);
};


#endif //UOSM_DASHBOARD_SDL_LOGVIEW_HPP
