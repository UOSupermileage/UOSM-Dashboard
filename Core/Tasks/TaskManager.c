//
// Created by Jeremy Cote on 2023-07-25.
//

// Can be removed if causing compilation issues on other systems
#include "TaskManager.h"
#include "LVGLTimerTask.h"
#include "InternalCommsTask.h"

void RunTaskManager(DataAggregatorWrapper* wrapper) {
    DebugPrint("Starting Task Manager...");
    InitLVGLTimerTask(wrapper);
    InitInternalCommsTask();
}