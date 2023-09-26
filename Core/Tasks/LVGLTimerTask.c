/*
 * LVGLTimerTask.c
 *
 *  Created on: Jul 23, 2023
 *      Author: jeremycote
 *
 * 	LVGL timer for tasks.
 */

#include "LVGLTimerTask.h"
#include "lvgl/lvgl.h"

#define STACK_SIZE (1024*3)
#define LVGL_TIMER_TASK_PRIORITY (osPriority_t) osPriorityNormal
#define TIMER_LVGL_TIMER_TASK 10UL

const char LVGL_TIMER_TAG[] = "#LVGL_TIM:";

osThreadId_t LVGLTimerTaskHandle;
const osThreadAttr_t LVGLTimerTask_attributes = {
        .name = "LVGLTimerTask",
        .stack_size = STACK_SIZE,
        .priority = LVGL_TIMER_TASK_PRIORITY,
};

static DataAggregatorWrapper* wrapper;

PUBLIC void InitLVGLTimerTask(DataAggregatorWrapper* w) {
    wrapper = w;
    LVGLTimerTaskHandle = osThreadNew(LVGLTimerTask, NULL, &LVGLTimerTask_attributes);
}

PRIVATE void LVGLTimerTask(void* argument) {
    uint32_t cycleTick = osKernelGetTickCount();
    DebugPrint("%s LVLG Timer Task", LVGL_TIMER_TAG);
    for (;;) {
        lv_timer_handler();

        cycleTick += TIMER_LVGL_TIMER_TASK;
        osDelayUntil(cycleTick);
    }
}
