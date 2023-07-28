//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_VIEW_H
#define UOSM_DASHBOARD_VIEW_H

#include "lvgl/lvgl.h"
#include "ViewModel.hpp"
#include "Styles.hpp"

/**
 * Create an LVGL view with parent.
 * Binds the model to this view.
 * If parent is NULL, the returned pointer will point to a screen.
 * Else, the returned pointer is the container holding all view elements. This container is a child of the passed parent.
 */
class View {
private:
    lv_obj_t* container;

protected:
    /**
     * Construct an LVGL object
     * @param parent
     */
    explicit View(lv_obj_t* parent);

    ~View();

public:
    lv_obj_t* GetContainer() {
        return container;
    }
};


#endif //UOSM_DASHBOARD_VIEW_H
