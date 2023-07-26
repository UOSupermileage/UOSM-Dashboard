/*
 * InternalCommsTask.H
 *
 *  Created on: Jul 23, 2023
 *      Author: jeremycote
 *
 * 	Communication between microcontrollers.
 */

#ifndef TASKS_INTERNALCOMMSTASK_H_
#define TASKS_INTERNALCOMMSTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32f7xx_hal.h"

// Our headers
#include "ApplicationTypes.h"


PUBLIC void InitInternalCommsTask(void);
PRIVATE void InternalCommsTask(void *argument);


#endif /* TASKS_INTERNALCOMMSTASK_H_ */
