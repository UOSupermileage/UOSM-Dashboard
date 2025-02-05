//
// Created by Jeremy Cote on 2023-07-28.
// Edited by Annique Granchelli on 2024-01-29
//

#include "HomeView.hpp"
#include "Utils/montserrat_72.c"
// add font
// LV_FONT_DECLARE(montserrat_72);

#define MAX_SPEED 45

static void set_value(void * bar, int32_t v)
{
    lv_bar_set_value((lv_obj_t*) bar, v, LV_ANIM_OFF);
}

static void event_cb(lv_event_t * e)
{
}

// get card
// ---------------------
// Title
//        Value
// ---------------------
lv_obj_t * get_card(lv_obj_t * parent, const char * title, const char * value, const int32_t width, const int32_t height) {
    lv_obj_t * card = lv_obj_create(parent);
    lv_obj_remove_style_all(card);
    lv_obj_set_size(card, width, height);
    // lv_obj_set_style_bg_color(card, lv_color_hex(0x00FF00), 0);
    // set grid layout
    static int32_t col_dsc[] = {width, LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {height/4, (height/4)*3, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(card, col_dsc, row_dsc);
    lv_obj_set_layout(card, LV_LAYOUT_GRID);
    lv_obj_set_grid_align(card, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_CENTER);
    lv_obj_set_style_pad_row(card, 0, 0);
    lv_obj_set_style_pad_column(card, 0, 0);

    lv_obj_t * title_label = lv_label_create(card);
    lv_label_set_text(title_label, title);
    lv_obj_set_grid_cell(title_label, LV_GRID_ALIGN_START, 0, 1,
                         LV_GRID_ALIGN_CENTER, 0, 1);

    lv_obj_t * value_label = lv_label_create(card);
    lv_label_set_text(value_label, value);
    lv_obj_set_grid_cell(value_label, LV_GRID_ALIGN_CENTER, 0, 1,
                         LV_GRID_ALIGN_CENTER, 1, 1);
    lv_obj_set_style_text_align(value_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(value_label, &montserrat_72, 0);


    return card;

}

// speed section
// ---------------------
// Speed
//        45
// ---------------------
// RPM

//        5000

// ---------------------
lv_obj_t * create_speed_section(lv_obj_t * parent, const int32_t width, const int32_t height)
{
    static int32_t col_dsc[] = {width, LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {height/2, height/2, LV_GRID_TEMPLATE_LAST};

    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_remove_style_all(cont);
    lv_obj_set_grid_align(cont, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_CENTER);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    lv_obj_set_size(cont, width, height);
    lv_obj_set_layout(cont, LV_LAYOUT_GRID);
    lv_obj_set_style_pad_row(cont, 0, 0);
    lv_obj_set_style_pad_column(cont, 0, 0);
    // bg color blue
    // lv_obj_set_style_bg_color(cont, lv_color_hex(0x0000FF), 0);
    // remove default container style

    // speed
    lv_obj_t * speed_card = get_card(cont, "Speed", "45", width, height/2);
    lv_obj_t * rpm_card = get_card(cont, "RPM", "5000", width, height/2);
    lv_obj_set_grid_cell(speed_card, LV_GRID_ALIGN_STRETCH, 0, 1,
                         LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_grid_cell(rpm_card, LV_GRID_ALIGN_STRETCH, 0, 1,
                         LV_GRID_ALIGN_STRETCH, 1, 1);

    return cont;
}

HomeView::HomeView(lv_obj_t* parent, DataAggregator& aggregator) : View(parent, aggregator) {
    // get resoltion of the screen
    lv_obj_t * cont = getContainer();

    DebugPrint("res : %d, %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);

    static int32_t col_dsc[] = {SCREEN_WIDTH/2 -1, 2, SCREEN_WIDTH/2 -1, LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {SCREEN_HEIGHT/2 -1, 2, SCREEN_HEIGHT/2 -1, LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    // lv_obj_t * cont = lv_obj_create(lv_screen_active());
    // lv_obj_t * cont = parent;
    lv_obj_set_grid_align(cont, LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_END);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    // lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    // lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_center(cont);
    // lv_obj_set_layout(cont, LV_LAYOUT_GRID);

    lv_obj_t * label;
    lv_obj_t * obj;

    uint32_t i;
    for(i = 0; i < 4; i++) {
        uint8_t col = i % 2;
        uint8_t row = i / 2;

        if (col == 1) {
            col++;
        }
        if (row == 1) {
            row++;
        }

        // obj = lv_button_create(cont);
        obj = create_speed_section(cont, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        /*Stretch the cell horizontally and vertically too
         *Set span to 1 to make the cell 1 column/row sized*/
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 1,
                             LV_GRID_ALIGN_STRETCH, row, 1);

        // label = lv_label_create(obj);
        // lv_label_set_text_fmt(label, "c%d, r%d", col, row);
        // lv_obj_center(label);
    }

    // add vertical separator
    lv_obj_t * separator = lv_obj_create(cont);
    lv_obj_set_size(separator, 2, SCREEN_HEIGHT);
    lv_obj_set_style_bg_color(separator, lv_color_hex(0x000000), 0);
    lv_obj_set_grid_cell(separator, LV_GRID_ALIGN_CENTER, 1, 1,
                         LV_GRID_ALIGN_CENTER, 0, 3);

    // add horizontal separator
    lv_obj_t * separator2 = lv_obj_create(cont);
    lv_obj_set_size(separator2, SCREEN_WIDTH, 2);
    lv_obj_set_style_bg_color(separator2, lv_color_hex(0x000000), 0);
    lv_obj_set_grid_cell(separator2, LV_GRID_ALIGN_CENTER, 0, 3,
                         LV_GRID_ALIGN_CENTER, 1, 1);

    lv_obj_set_style_pad_column(cont, 0, 0);
    lv_obj_set_style_pad_row(cont, 0, 0);
}
