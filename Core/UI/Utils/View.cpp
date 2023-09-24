//
// Created by Jeremy Cote on 2023-07-28.
//

#include "View.hpp"

View::View(lv_obj_t* parent, DataAggregator& aggregator): aggregator(aggregator) {
    this->container = lv_obj_create(parent);
    lv_style_set_flex_grow(container->styles->style, 1);
}

View::~View() {
    for (const auto& token: tokens) {
        token.cancel();
    }

    lv_obj_del(this->container);
}