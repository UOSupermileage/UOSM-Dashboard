//
// Created by Jeremy Cote on 2023-07-28.
//

#include "LightStyles.hpp"

LightStyles::LightStyles() {
    lv_style_init(&extraLargeTextStyle);
    lv_style_set_text_font(&extraLargeTextStyle, &sf_144);

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
}

lv_style_t* LightStyles::GetExtraLargeTextStyle() {
    return &extraLargeTextStyle;
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