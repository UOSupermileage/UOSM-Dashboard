//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_LIGHTSTYLES_HPP
#define UOSM_DASHBOARD_LIGHTSTYLES_HPP

#include "Styles.hpp"

class LightStyles : public Styles {
private:
    lv_style_t extraLargeTextStyle = {};

public:
    LightStyles();
    ~LightStyles() = default;

    lv_style_t* GetExtraLargeTextStyle() override;
};


#endif //UOSM_DASHBOARD_LIGHTSTYLES_HPP
