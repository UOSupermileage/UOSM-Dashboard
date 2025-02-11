//
// Created by toxo on 2/10/25.
//

#include "Cards.h"

#include <src/misc/lv_event_private.h>

#include "Utils/montserrat_72.c"
// add font
// LV_FONT_DECLARE(montserrat_72);

Card::Card(lv_obj_t * parent, const char * title, const char * value, const int32_t width, const int32_t height) : width(width), height(height) {
    card = lv_obj_create(parent);
    lv_obj_remove_style_all(card);
    lv_obj_set_size(card, width, height);
    // lv_obj_set_style_bg_color(card, lv_color_hex(0x00FF00), 0);
    // set grid layout
    static int32_t col_dsc[] = {width, LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {height/3, (height/3)*2, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(card, col_dsc, row_dsc);
    lv_obj_set_layout(card, LV_LAYOUT_GRID);
    lv_obj_set_grid_align(card, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_CENTER);
    lv_obj_set_style_pad_row(card, 0, 0);
    lv_obj_set_style_pad_column(card, 0, 0);

    title_label = lv_label_create(card);
    lv_label_set_text(title_label, title);
    lv_obj_set_grid_cell(title_label, LV_GRID_ALIGN_START, 0, 1,
                         LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_36, 0);

    value_label = lv_label_create(card);
    lv_label_set_text(value_label, value);
    lv_obj_set_grid_cell(value_label, LV_GRID_ALIGN_CENTER, 0, 1,
                         LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_style_text_align(value_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(value_label, &montserrat_72, 0);
}

DualCardInfo::DualCardInfo(lv_obj_t * parent, const char * title1, const char * value1, const char * title2, const char * value2, const int32_t width, const int32_t height) : width(width), height(height) {
    static int32_t col_dsc[] = {width, LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {height/2, height/2, LV_GRID_TEMPLATE_LAST};

    dualCard = lv_obj_create(parent);
    lv_obj_remove_style_all(dualCard);
    lv_obj_set_grid_align(dualCard, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_CENTER);
    lv_obj_set_grid_dsc_array(dualCard, col_dsc, row_dsc);
    lv_obj_set_size(dualCard, width, height);
    lv_obj_set_layout(dualCard, LV_LAYOUT_GRID);
    lv_obj_set_style_pad_row(dualCard, 0, 0);
    lv_obj_set_style_pad_column(dualCard, 0, 0);
    // bg color blue
    // lv_obj_set_style_bg_color(cont, lv_color_hex(0x0000FF), 0);
    // remove default container style

    // speed
    card1 = new Card(dualCard, title1, value1, width, height/2);
    card2 = new Card(dualCard, title2, value2, width, height/2);
    lv_obj_set_grid_cell(card1->get_card(), LV_GRID_ALIGN_STRETCH, 0, 1,
                         LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_grid_cell(card2->get_card(), LV_GRID_ALIGN_STRETCH, 0, 1,
                         LV_GRID_ALIGN_STRETCH, 1, 1);
}

DualCardInfo::~DualCardInfo() {
    // delete card1;
    // delete card2;
}