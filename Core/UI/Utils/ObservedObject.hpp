//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_OBSERVEDOBJECT_HPP
#define UOSM_DASHBOARD_OBSERVEDOBJECT_HPP

#include <functional>
#include <unordered_map>
#include <iostream>
#include <utility>
#include "Identifiable.hpp"

class ObserverToken : public Identifiable {
public:
    std::function<void()> cancel;

    explicit ObserverToken(std::function<void()> cancel) : cancel(std::move(cancel)) {}
};

template<typename T>
class Listener : public Identifiable {
public:
    std::function<void(const T&)> onChange;

    explicit Listener(std::function<void(const T&)> onChange) {
        this->onChange = onChange;
    }
};

template<typename T>
class ObservedObject {
public:
    explicit ObservedObject(const T& value) : value(value) {}

    // Getter
    T get() const { return value; }

    // Setter
    void set(const T& value) {
        if (this->value != value) {
            this->value = value;
            notify();
        }
    }

    // Force publish changes, listeners are also notified when using set.
    void publish() {
        notify();
    }

    /**
     *  Add a listener and return a token with a pointer to this object and a cancel lambda
     */
    ObserverToken addListener(std::function<void(const T&)> callback) {
        listeners.emplace_back(Listener<T>(callback));

        uint32_t listenerId = Listener<T>::getNextId();

        std::function<void()> cancel = {[this, listenerId]() {
            listeners.erase(std::remove_if(listeners.begin(), listeners.end(), [listenerId](Listener<T>& listener) {
                return listener.getId() == listenerId;
            }), listeners.end());
        }};

        return ObserverToken(cancel);
    }

private:
    T value;
    std::vector<Listener<T>> listeners;

    // Notify all registered listeners
    void notify() {
        for (const auto& listener: listeners) {
            listener.onChange(value);
        }
    }
};

#endif //UOSM_DASHBOARD_OBSERVEDOBJECT_HPP

// CURRENTLY UNUSED: TEMPLATE SPECIALIZATION FOR AN ARRAY
//template<typename T, size_t N>
//class ObservedObject<T[N]> {
//public:
//    explicit ObservedObject(T values[N]) : values(values) {
//
//    }
//
//    // Getter
//    [[nodiscard]] T* get() const { return values; }
//
//    // Setter
//    void set(T values[N]) {
//        this->values = values;
//        notify();
//    }
//
//    // Force publish changes, listeners are also notified when using set.
//    void publish() {
//        notify();
//    }
//
//    /**
//     *  Add a listener and return a token with a pointer to this object and a cancel lambda
//     */
//    ObserverToken addListener(std::function<void(const T&)> callback) {
//        listeners.emplace_back(Listener<T>(callback));
//
//        uint32_t listenerId = Listener<T>::getNextId();
//
//        std::function<void()> cancel = {[this, listenerId]() {
//            listeners.erase(std::remove_if(listeners.begin(), listeners.end(), [listenerId](Listener<T>& listener) {
//                return listener.getId() == listenerId;
//            }), listeners.end());
//        }};
//
//        return ObserverToken(cancel);
//    }
//
//private:
//    T values[N];
//    std::vector<Listener<T[N]>> listeners;
//
//    // Notify all registered listeners
//    void notify() {
//        for (const auto& listener: listeners) {
//            listener.onChange(values);
//        }
//    }
//};