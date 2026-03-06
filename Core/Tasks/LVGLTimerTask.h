/*
 * LVGLTimerTask.h
 *
 *  Created on: Jul 23, 2023
 *      Author: jeremycote
 */

#ifndef TASKS_LVGLTIMERTASK_H_
#define TASKS_LVGLTIMERTASK_H_

#ifdef __cplusplus
extern "C" {
#endif

// STM headers
#include "cmsis_os.h"
#include "stm32f7xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

#include "DataAggregatorWrapper.h"

PUBLIC void InitLVGLTimerTask(DataAggregatorWrapper* wrapper);

PRIVATE void LVGLTimerTask(void *argument);

void LVGL_Lock(void);
void LVGL_Unlock(void);

#ifdef __cplusplus
}
#endif

#endif /* TASKS_LVGLTIMERTASK_H_ */
