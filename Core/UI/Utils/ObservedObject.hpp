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

/** @ingroup core-ui-utils
 *  A class that represents a token that can be used to cancel an observation.
 *  It holds a function that can be called to cancel the observation.
 */
class ObserverToken : public Identifiable {
public:
    /** The function that can be called to cancel the observation. */
    std::function<void()> cancel;

    /** Constructs an observer token with a given cancel function.
     *  @param cancel The function that can be called to cancel the observation.
     */
    explicit ObserverToken(std::function<void()> cancel) : cancel(std::move(cancel)) {}
};

/** @ingroup core-ui-utils
 *  A class that represents a listener that can be notified of changes in an observed object.
 *  It holds a function that can be called with the new value of the observed object.
 */
template<typename T>
class Listener : public Identifiable {
public:
    /** The function that can be called with the new value of the observed object. */
    std::function<void(const T&)> onChange;

    /** Constructs a listener with a given onChange function.
     *  @param onChange The function that can be called with the new value of the observed object.
     */
    explicit Listener(std::function<void(const T&)> onChange) {
        this->onChange = onChange;
    }
};

/**
 * @ingroup core-ui-utils
 * @brief A class that represents an object that can be observed by listeners.
 *
 * The class allows registering listeners that will be notified when the object's value changes or when the object publishes changes.
 * The class is templated on the type of the value that the object holds.
 *
 * @tparam T The type of the value that the object holds.
 */
template<typename T>
class ObservedObject {
public:
    /**
     * @brief Construct a new ObservedObject with a given initial value.
     *
     * @param value The initial value of the object.
     */
    explicit ObservedObject(const T& value) {
        this->value = T(value);
    }

    /**
     * @brief Const a new ObservedObject where the observed object is held externally
     * @param value
     */
    explicit ObservedObject(T* value) : value(value) {}

    /**
     * @brief Get the current value of the object.
     *
     * @return T The current value of the object.
     */
    T get() const { return value; }

    /**
     * @brief Get a pointer to the current value of the observed object.
     * Make sure to call publish on the observed object once your changes are complete to notify listeners.
     * This is useful when the observed object is a class.
     * @return a mute
     */
    T* getMutable() { return &value; }

    /**
     * @brief Set a new value for the object and notify the listeners if the value is different from the previous one.
     *
     * @param value The new value for the object.
     */
    void set(const T& value) {
        if (this->value != value) {
            this->value = value;
            notify();
        }
    }

    /**
     * @brief Force publish changes to the listeners, regardless of whether the value has changed or not.
     */
    void publish() {
        notify();
    }

    /**
    * @brief Add a listener and return a token with a pointer to this object and a cancel lambda.
    *
    * The listener is a function that takes the current value of the object as a parameter and performs some action.
    * The token is an object that allows canceling the listener by calling its cancel() method.
    *
    * @param callback The listener function to be registered.
    * @return ObserverToken The token that allows canceling the listener.
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
    /**
     * @brief The value that the object holds
     */
    T* value;
    /**
     * @brief The list of registered listeners
     */
    std::vector<Listener<T>> listeners;

    /**
     * @brief Notify all registered listeners with the current value of the object.
     */
    void notify() {
        for (const auto& listener: listeners) {
            listener.onChange(value);
        }
    }
};

#endif //UOSM_DASHBOARD_OBSERVEDOBJECT_HPP