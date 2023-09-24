//
// Created by Jeremy Cote on 2023-08-24.
//

#ifndef UOSM_DASHBOARD_SDL_BARCHART_HPP
#define UOSM_DASHBOARD_SDL_BARCHART_HPP

#include "Chart.hpp"

class BarChart : public Chart {
public:
    BarChart(lv_obj_t* parent, DataAggregator& aggregator, std::initializer_list<ChartData> data);
};

#endif //UOSM_DASHBOARD_SDL_BARCHART_HPP
