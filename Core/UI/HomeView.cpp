//
// Created by Jeremy Cote on 2023-07-28.
// Edited by Annique Granchelli on 2024-01-29
//

#include "HomeView.hpp"
#include "StylesManager.hpp"

static lv_obj_t* stopCountMeter;


static void set_value(lv_meter_indicator_t* indic, int32_t v) {
    lv_meter_set_indicator_end_value(stopCountMeter, indic, v);
}

static uint32_t calculate_joule(uint32_t volt, uint32_t current) {
    return volt * current;
}

HomeView::HomeView(lv_obj_t* parent, DataAggregator& aggregator) : View(parent, aggregator) {
    Styles* styles = StylesManager::GetStyles();

    lv_obj_t* container = getContainer();
    lv_obj_add_style(container, styles->GetFullscreenViewStyle(), LV_PART_MAIN);

    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

    bottomRow = lv_obj_create(container);
    lv_obj_set_width(bottomRow, lv_obj_get_width(container));
    lv_obj_add_style(bottomRow, styles->GetFullscreenRowStyle(), LV_PART_MAIN);

    lv_obj_set_flex_grow(bottomRow, 1);

    lv_obj_t* efficiency_chart;
    efficiency_chart = lv_chart_create(bottomRow);
    lv_obj_set_size(efficiency_chart, 800, 460);
    lv_obj_center(efficiency_chart);
    lv_chart_set_type(efficiency_chart, LV_CHART_TYPE_BAR);
    lv_chart_set_update_mode(efficiency_chart, LV_CHART_UPDATE_MODE_CIRCULAR);
    lv_chart_set_point_count(efficiency_chart, 4);
    lv_chart_set_range(efficiency_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 200);

    lv_style_t style;
    lv_style_set_line_width(&style, 20);

    lv_obj_add_style(efficiency_chart, &style, LV_PART_MAIN);

    lv_chart_series_t* efficiencies = lv_chart_add_series(efficiency_chart, lv_palette_main(LV_PALETTE_INDIGO),
                                                          LV_CHART_AXIS_PRIMARY_Y);


    getDataAggregator().efficiency.addListener([efficiency_chart, efficiencies](const lap_efficiencies_t& e) {
        DebugPrint("Displaying efficiencies: %d %d %d %d", e.lap_0, e.lap_1, e.lap_2, e.lap_3);

        lv_chart_set_next_value(efficiency_chart, efficiencies, 200);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_1);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_2);
        lv_chart_set_next_value(efficiency_chart, efficiencies, e.lap_3);

        lv_chart_refresh(efficiency_chart);
    });
}
