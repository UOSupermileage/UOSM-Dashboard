//
// Created by Jeremy Cote on 2023-07-28.
//

#include "View.hpp"

#include <src/core/lv_obj_private.h>
#include <src/core/lv_obj_style_private.h>

View::View(lv_obj_t* parent, DataAggregator& aggregator): aggregator(aggregator) {
    this->container = lv_obj_create(parent);
    lv_style_set_flex_grow(container->styles->style, 1);
}

View::~View() {
    lv_obj_del(this->container);
}