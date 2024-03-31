//
// Created by Jeremy Cote on 2023-07-28.
// Edited by Annique Granchelli on 2024-01-29
//

#include "HomeView.hpp"

#define MAX_SPEED 45

static void set_value(void * bar, int32_t v)
{
    lv_bar_set_value((lv_obj_t*) bar, v, LV_ANIM_OFF);
}

static void event_cb(lv_event_t * e)
{
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    if(dsc->part != LV_PART_INDICATOR) return;

    lv_obj_t * obj = lv_event_get_target(e);

    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.font = &lv_font_montserrat_30;

    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d", (int)lv_bar_get_value(obj));

    lv_point_t txt_size;
    lv_txt_get_size(&txt_size, buf, label_dsc.font, label_dsc.letter_space, label_dsc.line_space, LV_COORD_MAX,
                    label_dsc.flag);

    lv_area_t txt_area;
    /*If the indicator is long enough put the text inside on the right*/
    if(lv_area_get_width(dsc->draw_area) > txt_size.x + 20) {
        txt_area.x2 = dsc->draw_area->x2 - 5;
        txt_area.x1 = txt_area.x2 - txt_size.x + 1;
        label_dsc.color = lv_color_white();
    }
        /*If the indicator is still short put the text out of it on the right*/
    else {
        txt_area.x1 = dsc->draw_area->x2 + 5;
        txt_area.x2 = txt_area.x1 + txt_size.x - 1;
        label_dsc.color = lv_color_black();
    }

    txt_area.y1 = dsc->draw_area->y1 + (lv_area_get_height(dsc->draw_area) - txt_size.y) / 2;
    txt_area.y2 = txt_area.y1 + txt_size.y - 1;

    lv_draw_label(dsc->draw_ctx, &label_dsc, &txt_area, buf, NULL);
}

HomeView::HomeView(lv_obj_t* parent, DataAggregator& aggregator) : View(parent, aggregator) {
    lv_obj_t* container = getContainer();

    lv_style_t fullscreenViewStyle;
    lv_style_init(&fullscreenViewStyle);
    lv_style_set_pad_all(&fullscreenViewStyle, 0);
    lv_style_set_pad_row(&fullscreenViewStyle, 0);
    lv_style_set_bg_color(&fullscreenViewStyle, LV_COLOR_MAKE(255, 255, 255));

    lv_obj_add_style(container, &fullscreenViewStyle, LV_PART_MAIN);

    DebugPrint("Flex column");

    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

    lv_style_t fullscreenRowStyle;
    lv_style_init(&fullscreenRowStyle);
    lv_style_set_bg_opa(&fullscreenRowStyle, 0);
    lv_style_set_border_width(&fullscreenRowStyle, 0);

    DebugPrint("Creating bottomRow");

    topRow = lv_obj_create(container);
    lv_obj_set_width(topRow, lv_obj_get_width(container));
    lv_obj_set_height(topRow, 100);
    lv_obj_add_style(topRow, &fullscreenRowStyle, LV_PART_MAIN);

    lv_obj_t *bar = lv_bar_create(topRow);
    lv_obj_add_event_cb(bar, event_cb, LV_EVENT_DRAW_PART_END, NULL);
    lv_obj_set_size(bar, SCREEN_WIDTH - 40, 50);
    lv_obj_center(bar);

    lv_bar_set_range(bar, 0, MAX_SPEED);

    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

    static lv_grad_dsc_t grad_dsc;

    grad_dsc.dir = LV_GRAD_DIR_HOR;
    grad_dsc.stops_count = 3;

    grad_dsc.stops[0].color = lv_palette_main(LV_PALETTE_DEEP_ORANGE);
    grad_dsc.stops[0].frac = 0;

    grad_dsc.stops[1].color = lv_palette_main(LV_PALETTE_GREEN);
    grad_dsc.stops[1].frac = 255 * 25 / MAX_SPEED;

    grad_dsc.stops[2].color = lv_palette_main(LV_PALETTE_RED);
    grad_dsc.stops[2].frac = 255 * 35 / MAX_SPEED;

    lv_style_set_bg_grad(&style_indic, &grad_dsc);

    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);

    bottomRow = lv_obj_create(container);
    lv_obj_set_width(bottomRow, lv_obj_get_width(container));
    lv_obj_set_height(bottomRow, SCREEN_HEIGHT - 100);
    lv_obj_add_style(bottomRow, &fullscreenRowStyle, LV_PART_MAIN);

    DebugPrint("Creating efficiency chart");

    lv_obj_t* efficiency_chart;
    efficiency_chart = lv_chart_create(bottomRow);
    lv_obj_set_size(efficiency_chart, 800, SCREEN_HEIGHT - 100);
    lv_obj_center(efficiency_chart);

    lv_chart_set_type(efficiency_chart, LV_CHART_TYPE_BAR);
    lv_chart_set_update_mode(efficiency_chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_point_count(efficiency_chart, 4);
    lv_chart_set_range(efficiency_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 200);

    DebugPrint("Adding efficiency series");
    lv_chart_series_t* efficiencies = lv_chart_add_series(efficiency_chart, lv_palette_main(LV_PALETTE_INDIGO),
                                                          LV_CHART_AXIS_PRIMARY_Y);
    getDataAggregator().speed.addListener([bar](const speed_t& speed) {
        set_value(bar, speed / 1000);
    });

    getDataAggregator().efficiency.addListener([efficiency_chart, efficiencies, bar](const lap_efficiencies_t& e) {
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_0);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_1);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_2);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_3);

        lv_chart_refresh(efficiency_chart);
    });
}
