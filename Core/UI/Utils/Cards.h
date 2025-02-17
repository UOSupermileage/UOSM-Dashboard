//
// Created by toxo on 2/10/25.
//

#ifndef CARDS_H
#define CARDS_H

#include <lvgl/lvgl.h>

class Card {
public:
    Card(lv_obj_t * parent, const char * title, const char * value, const int32_t width, const int32_t height);

    lv_obj_t * get_card() {
        return card;
    }

    lv_obj_t * get_title_label() {
        return title_label;
    }

    lv_obj_t * get_value_label() {
        return value_label;
    }

private:
    lv_obj_t * card;
    lv_obj_t * title_label;
    lv_obj_t * value_label;
    int32_t width;
    int32_t height;
};

class DualCardInfo {
public:
    DualCardInfo() {}
    DualCardInfo(lv_obj_t * parent, const char * title1, const char * value1, const char * title2, const char * value2, const int32_t width, const int32_t height);

    ~DualCardInfo();

    lv_obj_t * get_dualCard() const {
        return dualCard;
    }

    Card * get_card1() const {
        return card1;
    }

    Card * get_card2() const {
        return card2;
    }

private:
    lv_obj_t * dualCard;
    Card * card1;
    Card * card2;
    int32_t width;
    int32_t height;

};



#endif //CARDS_H
