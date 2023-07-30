//
// Created by Jeremy Cote on 2023-07-27.
//

#ifndef UOSM_DASHBOARD_STYLES_HPP
#define UOSM_DASHBOARD_STYLES_HPP

#include "lvgl/lvgl.h"

class Styles {
public:
    virtual lv_style_t* GetExtraLargeTextStyle() = 0;
    virtual lv_style_t* GetFullscreenChartStyle() = 0;
};

#endif //UOSM_DASHBOARD_STYLES_HPP
