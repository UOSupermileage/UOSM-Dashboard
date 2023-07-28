//
// Created by Jeremy Cote on 2023-07-27.
//

#include "styles.hpp"

lv_style_t extraLargeTextStyle;

void Styles_Init() {
    lv_style_init(&extraLargeTextStyle);
    lv_style_set_text_font(&extraLargeTextStyle, &lv_font_montserrat_48);
}