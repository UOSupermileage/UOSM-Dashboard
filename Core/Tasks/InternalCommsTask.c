/*
 * InternalCommsTask.c
 *
 *  Created on: Jul 23, 2023
 *      Author: jeremycote
 *
 * 	Communication between microcontrollers.
 */

#include "InternalCommsTask.h"
#include "InternalCommsModule.h"

#include "CANCallbacks.h"

#define STACK_SIZE (1024*4)
#define INTERNAL_COMMS_TASK_PRIORITY (osPriority_t) osPriorityHigh
#define TIMER_INTERNAL_COMMS_TASK 200UL

const char ICT_TAG[] = "#ICT:";

osThreadId_t InternalCommsTaskHandle;
const osThreadAttr_t InternalCommsTask_attributes = {
        .name = "InternalCommunications",
        .stack_size = STACK_SIZE,
        .priority = INTERNAL_COMMS_TASK_PRIORITY,
};

PUBLIC void InitInternalCommsTask(void) {
    InternalCommsTaskHandle = osThreadNew(InternalCommsTask, NULL, &InternalCommsTask_attributes);
}

// Polls can bus for new data
PRIVATE void InternalCommsTask(void* argument) {
    uint32_t cycleTick = osKernelGetTickCount();
    DebugPrint("Starting Internal Communication Task");

    IComms_Init();
    for (;;) {
        cycleTick += TIMER_INTERNAL_COMMS_TASK;
        osDelayUntil(cycleTick);

        DebugPrint(".");
        IComms_PeriodicReceive();
    }
}