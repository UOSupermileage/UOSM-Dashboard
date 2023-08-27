//
// Created by Jeremy Cote on 2023-08-24.
//

#ifndef UOSM_DASHBOARD_SDL_CHART_HPP
#define UOSM_DASHBOARD_SDL_CHART_HPP


#include "View.hpp"
#include "ObservedDataQueue.hpp"
#include <vector>
#include <initializer_list>

struct ChartData {
    ObservedDataQueue<lv_coord_t>& data;
    bool displayed;

    explicit ChartData(ObservedDataQueue<lv_coord_t>& data, bool displayed = true): data(data), displayed(displayed) {}
};

class ChartViewModel: public ViewModel {
private:
    std::vector<ObservedObject<ChartData>> items;

public:
    explicit ChartViewModel(DataAggregator& aggregator, std::initializer_list<ChartData> data): ViewModel(aggregator) {
        for (ChartData item : data) {
            // Use emplace_back to construct the observed object directly inside the vector. This eliminates a copy instruction.
            items.emplace_back(item);
        }
    }

    /**
     * @return a readonly reference to a chart model's observed items.
     */
    [[nodiscard]] const std::vector<ObservedObject<ChartData>>& getItems() const {
        return items;
    }
};

class Chart: public View {
private:
    ChartViewModel& viewModel;

    /** Pointer to the chart managed by this view. */
    lv_obj_t* chart;

protected:
    Chart(lv_obj_t* parent, ChartViewModel& viewModel): View(parent, viewModel), viewModel(viewModel) {
        chart = lv_chart_create(getContainer());
    };

    [[nodiscard]] lv_obj_t* getChart() {
        return chart;
    }
};


#endif //UOSM_DASHBOARD_SDL_CHART_HPP
