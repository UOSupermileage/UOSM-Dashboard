//
// Created by Jeremy Cote on 2023-09-23.
//

#include "LogView.hpp"
#include "StylesManager.hpp"

#define LOG_VIEW_N_COLUMNS 1
#define LOG_VIEW_PADDING 5

LogView::LogView(lv_obj_t* parent, DataAggregator& aggregator) : View(parent, aggregator) {
    Styles* styles = StylesManager::GetStyles();

    lv_obj_t* container = getContainer();
    lv_obj_add_style(container, styles->GetFullscreenViewStyle(), LV_PART_MAIN);

    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);

    // Create the actual table
    table = lv_table_create(container);

    lv_table_set_col_cnt(table, LOG_VIEW_N_COLUMNS);
    lv_table_set_col_width(table, 0, lv_obj_get_width(container) - LOG_VIEW_PADDING);

    // The number of rows is equal to the theoretical max size of the can logs entry buffer. In practice, this buffer is almost always full.
    lv_table_set_row_cnt(table, getDataAggregator().canLogEntries.getSize());

    lv_obj_align(table, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_width(table, lv_obj_get_width(container));

    getDataAggregator().canLogEntries.addListener([this](const DataQueue<CANLogEntry*>& entries) {
        // In case view is deleted, return before trying to access it.
        if (!this) {
            return;
        }

        for (auto iterator = entries.begin(); iterator != entries.end(); ++iterator) {
            lv_table_set_cell_value(table, iterator.getCurrentIndex(), 0, (*iterator)->getMessage());
        }

        // Set remaining rows to have empty strings in all columns.
        for (uint8_t i = entries.getNumberOfElements(); i < entries.getSize(); i++) {
            for (uint8_t j = 0; j < LOG_VIEW_N_COLUMNS; j++) {
                lv_table_set_cell_value(table, i, j, "");
            }
        }
    });
}
