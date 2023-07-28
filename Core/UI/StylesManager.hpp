//
// Created by Jeremy Cote on 2023-07-28.
//

#ifndef UOSM_DASHBOARD_STYLESMANAGER_HPP
#define UOSM_DASHBOARD_STYLESMANAGER_HPP

#include "Styles.hpp"
#include "LightStyles.hpp"

/**
 * Holds a reference to the currently active styles.
 */
class StylesManager {
private:
    static Styles* styles;

    StylesManager() {};
    ~StylesManager() = default;

public:
    static Styles* GetStyles();
};


#endif //UOSM_DASHBOARD_STYLESMANAGER_HPP
