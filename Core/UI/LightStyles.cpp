//
// Created by Jeremy Cote on 2023-07-28.
//

#include "LightStyles.hpp"

LV_FONT_DECLARE(montserrat_72)

LightStyles::LightStyles() {
    lv_style_init(&extraLargeTextStyle);
    lv_style_set_text_font(&extraLargeTextStyle, &sf_144);

    lv_style_init(&largeTextStyle);
    lv_style_set_text_font(&largeTextStyle, &montserrat_72);


    lv_style_init(&fullscreenChartStyle);
    lv_style_set_border_width(&fullscreenChartStyle, 10);
    lv_style_set_border_color(&fullscreenChartStyle, LV_COLOR_MAKE(0, 0, 0));
    lv_style_set_flex_grow(&fullscreenChartStyle, 2);

    lv_style_init(&fullscreenViewStyle);
    lv_style_set_pad_all(&fullscreenViewStyle, 0);
    lv_style_set_pad_row(&fullscreenViewStyle, 0);
    lv_style_set_bg_color(&fullscreenViewStyle, LV_COLOR_MAKE(255, 255, 255));

    lv_style_init(&fullscreenRowStyle);
    lv_style_set_bg_opa(&fullscreenRowStyle, 0);
    lv_style_set_border_width(&fullscreenRowStyle, 0);

    lv_style_init(&mainArcStyle);
    lv_style_set_arc_color(&mainArcStyle, LV_COLOR_MAKE(150, 150, 150));
    lv_style_set_arc_width(&mainArcStyle, 40);
    lv_style_set_arc_rounded(&mainArcStyle, false);

    lv_style_init(&throttleArcStyle);
    lv_style_set_arc_color(&throttleArcStyle, LV_COLOR_MAKE(100, 255, 100));
    lv_style_set_arc_width(&throttleArcStyle, 40);
    lv_style_set_arc_rounded(&throttleArcStyle, false);

    lv_style_init(&aiThrottleArcStyle);
    lv_style_set_arc_color(&aiThrottleArcStyle, LV_COLOR_MAKE(255, 100, 100));
    lv_style_set_arc_width(&aiThrottleArcStyle, 40);
    lv_style_set_arc_rounded(&aiThrottleArcStyle, false);
}

lv_style_t* LightStyles::GetExtraLargeTextStyle() {
    return &extraLargeTextStyle;
}

lv_style_t* LightStyles::GetLargeTextStyle() {
    return &largeTextStyle;
}

lv_style_t* LightStyles::GetFullscreenChartStyle() {
    return &fullscreenChartStyle;
}

lv_style_t* LightStyles::GetFullscreenViewStyle() {
    return &fullscreenViewStyle;
}

lv_style_t* LightStyles::GetFullscreenRowStyle() {
    return &fullscreenRowStyle;
}

lv_style_t* LightStyles::GetThrottleArcStyle() {
    return &throttleArcStyle;
}

lv_style_t* LightStyles::GetAiThrottleArcStyle() {
    return &aiThrottleArcStyle;
}

lv_style_t* LightStyles::GetMainArcStyle() {
    return &mainArcStyle;
}