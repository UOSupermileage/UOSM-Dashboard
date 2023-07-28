//
// Created by Jeremy Cote on 2023-07-27.
//

#ifndef UOSM_DASHBOARD_HOME_HPP
#define UOSM_DASHBOARD_HOME_HPP

#include "ApplicationTypes.h"
#include "lvgl/lvgl.h"

#define HOME_DATA_REFRESH_RATE 250

typedef struct HomeViewModel {
} HomeViewModel;

/**
 * Create an LVGL view with parent.
 * Binds the model to this view.
 * If parent is NULL, the returned pointer will point to a screen.
 * Else, the returned pointer is the container holding all view elements. This container is a child of the passed parent.
 */
PUBLIC lv_obj_t* Home_CreateView(lv_obj_t* parent, HomeViewModel* model);

/**
 * Returns a pointer to a new HomeViewModel
 */
PUBLIC HomeViewModel* Home_CreateViewModel();

#endif //UOSM_DASHBOARD_HOME_HPP
