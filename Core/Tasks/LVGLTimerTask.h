/*
 * LVGLTimerTask.h
 *
 *  Created on: Jul 23, 2023
 *      Author: jeremycote
 */

#ifndef TASKS_LVGLTIMERTASK_H_
#define TASKS_LVGLTIMERTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32f7xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

#include "DataAggregatorWrapper.h"

PUBLIC void InitLVGLTimerTask(DataAggregatorWrapper* wrapper);

PRIVATE void LVGLTimerTask(void *argument);

#endif /* TASKS_LVGLTIMERTASK_H_ */
