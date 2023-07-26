//
// Created by Jeremy Cote on 2023-07-25.
//

// Can be removed if causing compilation issues on other systems
#include "TaskManager.h"
#include "lvgl/lvgl.h"
#include "LVGLTimerTask.h"

void RunTaskManager(void) {
    DebugPrint("Starting Task Manager...");

//    while(1) {
//        lv_task_handler();
//        HAL_Delay(5);
//    }
    InitLVGLTimerTask();
}