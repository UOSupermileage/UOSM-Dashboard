//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_VIEW_H
#define UOSM_DASHBOARD_VIEW_H

#include <map>
#include <memory>
#include "lvgl/lvgl.h"
#include "DataAggregator.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

/** @ingroup core-ui-utils
 *  A class that represents a view that displays the data from a view model using LVGL widgets.
 *  It creates a container that holds all the view elements, and binds the view model to the view using observer tokens.
 */
class View {
private:
    /** The container that holds all the view elements. */
    lv_obj_t* container;

    /** Reference to the source of truth for this view. */
    DataAggregator& aggregator;

protected:
    /** Constructs a view with a given parent and a view model.
     *  @param parent The parent object of the container, or NULL if the container is a screen.
     *  @param viewModel The reference to the view model that provides the data for the view.
     */
    explicit View(lv_obj_t* parent, DataAggregator& aggregator);

    /** Destructs the view and releases the observer tokens. */
    ~View();

    DataAggregator& getDataAggregator() {
        return aggregator;
    }

public:
    /** Returns a pointer to the container that holds all the view elements.
     *  @return A pointer to the container that holds all the view elements.
     */
    lv_obj_t* getContainer() {
        return container;
    }
};


#endif //UOSM_DASHBOARD_VIEW_H
