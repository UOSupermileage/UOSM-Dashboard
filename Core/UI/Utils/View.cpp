//
// Created by Jeremy Cote on 2023-07-28.
//

#include "View.hpp"

View::View(lv_obj_t* parent) {
    this->container = lv_obj_create(parent);
}

View::~View() {
    lv_obj_del(this->container);
}