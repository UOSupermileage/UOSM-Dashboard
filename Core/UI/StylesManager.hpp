//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_STYLESMANAGER_HPP
#define UOSM_DASHBOARD_STYLESMANAGER_HPP

#include "Styles.hpp"
#include "LightStyles.hpp"

/** @ingroup core-ui
 *  A class that manages the styles for the dashboard.
 *  It holds a reference to the currently active styles and provides a static method to get the styles.
 */
class StylesManager {
private:
    /** The pointer to the currently active styles. */
    static Styles* styles;

    /** Constructs a styles manager object. */
    StylesManager() {};
    /** Destructs the styles manager object. */
    ~StylesManager() = default;

public:
    /** Returns a pointer to the currently active styles.
     *  @return A pointer to the currently active styles.
     */
    static Styles* GetStyles();
};


#endif //UOSM_DASHBOARD_STYLESMANAGER_HPP
