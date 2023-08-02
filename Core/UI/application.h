//
// Created by Jeremy Cote on 2023-07-25.
//

#ifndef UOSM_DASHBOARD_APPLICATION_H
#define UOSM_DASHBOARD_APPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ApplicationTypes.h"

#include "lvgl/lvgl.h"
#include "DataAggregatorWrapper.h"

/**
 * @ingroup core-ui
 * Creates the LVGL application.
 * @param aggregatorWrapper
 */
PUBLIC void Application_Create(DataAggregatorWrapper* aggregatorWrapper);

#ifdef __cplusplus
}
#endif

#endif //UOSM_DASHBOARD_APPLICATION_H