//
// Created by Jeremy Cote on 2023-08-24.
//

#ifndef UOSM_DASHBOARD_SDL_BARCHART_HPP
#define UOSM_DASHBOARD_SDL_BARCHART_HPP

#include "Chart.hpp"

class BarChartViewModel : public ChartViewModel {
public:
    explicit BarChartViewModel(DataAggregator& aggregator, std::initializer_list<ChartData> data) : ChartViewModel(
            aggregator, data) {};
};

class BarChart : public Chart {
public:
    BarChart(lv_obj_t* parent, BarChartViewModel& viewModel);
};

#endif //UOSM_DASHBOARD_SDL_BARCHART_HPP
