//
// Created by Jeremy Cote on 2023-07-28.
//

#include "LightStyles.hpp"

LightStyles::LightStyles() {
    lv_style_init(&extraLargeTextStyle);
    lv_style_set_text_font(&extraLargeTextStyle, &lv_font_montserrat_48);
}

lv_style_t* LightStyles::GetExtraLargeTextStyle() {
    return &extraLargeTextStyle;
}