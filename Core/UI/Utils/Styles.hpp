//
// Created by Jeremy Cote on 2023-07-27.
//

#ifndef UOSM_DASHBOARD_STYLES_HPP
#define UOSM_DASHBOARD_STYLES_HPP

#include "lvgl/lvgl.h"

/** @ingroup core-ui-utils
 *  A class that represents an abstract interface for different styles of the UI elements.
 *  It provides methods to get the styles for different components, such as text and charts.
 */
class Styles {
public:
    /** Returns a pointer to a style for extra large text.
     *  @return A pointer to a style for extra large text.
     */
    virtual lv_style_t* GetExtraLargeTextStyle() = 0;

    /** Returns a pointer to a style for fullscreen charts.
     *  @return A pointer to a style for fullscreen charts.
     */
    virtual lv_style_t* GetFullscreenChartStyle() = 0;

    /** Returns a pointer to a style for a fullscreen view.
     *  @return A pointer to a style for a fullscreen view.
     */
    virtual lv_style_t* GetFullscreenViewStyle() = 0;

    /** Returns a pointer to a style for a fullscreen row.
     * @return A pointer to a style for a fullscreen row.
     */
    virtual lv_style_t* GetFullscreenRowStyle() = 0;
};

#endif //UOSM_DASHBOARD_STYLES_HPP
