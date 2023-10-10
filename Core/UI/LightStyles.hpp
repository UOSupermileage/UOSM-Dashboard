//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_LIGHTSTYLES_HPP
#define UOSM_DASHBOARD_LIGHTSTYLES_HPP

#include "Styles.hpp"

/** @ingroup core-ui
 *  A class that represents a set of styles for the light theme of the dashboard.
 *  It inherits from the Styles class and defines specific style implementations for the light theme.
 */
class LightStyles : public Styles {
private:
    /** The style for extra large text, such as the battery voltage and motor RPM. */
    lv_style_t extraLargeTextStyle = {};
    /** The style for large text, such as the lap efficiency. */
    lv_style_t largeTextStyle = {};
    /** The style for fullscreen charts, such as the speed and power charts. */
    lv_style_t fullscreenChartStyle = {};
    /** The style for a fullscreen view, such as the main view. */
    lv_style_t fullscreenViewStyle = {};
    /** The style for a row in a fullscreen view. Should not be visible. */
    lv_style_t fullscreenRowStyle = {};
    /** The style for a throttle arc. */
    lv_style_t throttleArcStyle = {};
    /** The style for a ai throttle arc. */
    lv_style_t aiThrottleArcStyle = {};
    /** The style for a main arc. */
    lv_style_t mainArcStyle = {};

public:
    /** Constructs a light styles object and initializes its styles. */
    LightStyles();
    /** Destructs the light styles object. */
    ~LightStyles() = default;

    lv_style_t* GetExtraLargeTextStyle() override;
    lv_style_t* GetLargeTextStyle() override;
    lv_style_t* GetFullscreenChartStyle() override;
    lv_style_t* GetFullscreenViewStyle() override;
    lv_style_t* GetFullscreenRowStyle() override;
    lv_style_t* GetThrottleArcStyle() override;
    lv_style_t* GetAiThrottleArcStyle() override;
    lv_style_t* GetMainArcStyle() override;
};


#endif //UOSM_DASHBOARD_LIGHTSTYLES_HPP
