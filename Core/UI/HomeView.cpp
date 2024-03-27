//
// Created by Jeremy Cote on 2023-07-28.
// Edited by Annique Granchelli on 2024-01-29
//

#include "HomeView.hpp"

HomeView::HomeView(lv_obj_t* parent, DataAggregator& aggregator) : View(parent, aggregator) {
    lv_obj_t* container = getContainer();

    lv_style_t fullscreenViewStyle;
    lv_style_init(&fullscreenViewStyle);
    lv_style_set_pad_all(&fullscreenViewStyle, 0);
    lv_style_set_pad_row(&fullscreenViewStyle, 0);
    lv_style_set_bg_color(&fullscreenViewStyle, LV_COLOR_MAKE(255, 255, 255));

    lv_obj_add_style(container, &fullscreenViewStyle, LV_PART_MAIN);

    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

    lv_style_t fullscreenRowStyle;
    lv_style_init(&fullscreenRowStyle);
    lv_style_set_bg_opa(&fullscreenRowStyle, 0);
    lv_style_set_border_width(&fullscreenRowStyle, 0);

    bottomRow = lv_obj_create(container);
    lv_obj_set_width(bottomRow, lv_obj_get_width(container));
    lv_obj_add_style(bottomRow, &fullscreenRowStyle, LV_PART_MAIN);

    lv_obj_set_flex_grow(bottomRow, 1);

    lv_obj_t* efficiency_chart;
    efficiency_chart = lv_chart_create(bottomRow);
    lv_obj_set_size(efficiency_chart, 800, 460);
    lv_obj_center(efficiency_chart);
    lv_chart_set_type(efficiency_chart, LV_CHART_TYPE_BAR);
    lv_chart_set_update_mode(efficiency_chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_point_count(efficiency_chart, 4);
    lv_chart_set_range(efficiency_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 200);

    lv_style_t style;
    lv_style_set_line_width(&style, 20);

    lv_obj_add_style(efficiency_chart, &style, LV_PART_MAIN);

    lv_chart_series_t* efficiencies = lv_chart_add_series(efficiency_chart, lv_palette_main(LV_PALETTE_INDIGO),
                                                          LV_CHART_AXIS_PRIMARY_Y);

    getDataAggregator().efficiency.addListener([efficiency_chart, efficiencies](const lap_efficiencies_t& e) {
        DebugPrint("Displaying efficiencies: %d %d %d %d", e.lap_0, e.lap_1, e.lap_2, e.lap_3);

        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_0);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_1);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_2);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_3);

        lv_chart_refresh(efficiency_chart);
    });
}
