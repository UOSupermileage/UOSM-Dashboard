//
// Created by Jeremy Cote on 2023-08-24.
//

#include "BarChart.hpp"

BarChart::BarChart(lv_obj_t* parent, DataAggregator& aggregator, std::initializer_list<ChartData> data): Chart(parent, aggregator, data) {
    // TODO: Figure out automatic ticks
    // TODO: Figure out labels
    // TODO: Figure out multiple data sources in a bar graph, I'm thinking vertically stacked bars?
    // TODO: Hook chart into observed objects from the view model.
}