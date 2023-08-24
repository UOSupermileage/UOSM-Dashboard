//
// Created by Jeremy Cote on 2023-08-21.
//

#ifndef UOSM_DASHBOARD_SDL_OBSERVEDDATAQUEUE_HPP
#define UOSM_DASHBOARD_SDL_OBSERVEDDATAQUEUE_HPP

#include "DataQueue.hpp"
#include "ObservedObject.hpp"

/**
 *
 */
template<typename T>
class ObservedDataQueue: public DataQueue<T>, public ObservedObject<DataQueue<T>> {
public:
    explicit ObservedDataQueue(uint8_t size): DataQueue<T>(size), ObservedObject<DataQueue<T>>(this) {}
};

#endif //UOSM_DASHBOARD_SDL_OBSERVEDDATAQUEUE_HPP
