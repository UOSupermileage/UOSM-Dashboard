//
// Created by Jeremy Cote on 2023-07-28.
//

#include "StylesManager.hpp"

// This actually creates static styles variable
Styles* StylesManager::styles;

Styles* StylesManager::GetStyles() {
    if (StylesManager::styles == nullptr) {
        StylesManager::styles = new LightStyles();
    }

    return StylesManager::styles;
}