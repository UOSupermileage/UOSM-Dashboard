//
// Created by Jeremy Cote on 2023-08-05.
//

#ifndef UOSM_DASHBOARD_COMBINELATEST_HPP
#define UOSM_DASHBOARD_COMBINELATEST_HPP

#include <tuple>
#include <functional>
#include <optional>

#include "ObservedObject.hpp"

template<typename... Ts>
class CombineLatest {
public:
    using Callback = std::function<void(const Ts& ...)>;

    // Templated constructor to deduce the type of the lambda directly
    template<typename Func>
    explicit CombineLatest(Func&& callback, ObservedObject<Ts>& ... observedObjects)
            : callback(std::forward<Func>(callback)), objects(observedObjects...) {
        (observedObjects.addListener(std::bind(&CombineLatest::handleUpdate, this)), ...);
    }

    void handleUpdate() {
        auto latestValues = getLatestValues(objects, std::index_sequence_for<Ts...>{});
        if (std::apply([](const auto& ... args) { return (args && ...); }, latestValues)) {
            callCallback(latestValues);
        }
    }

private:
    // Helper function to get the latest values from ObservedObjects
    template<std::size_t... Is>
    static std::tuple<std::optional<Ts>...>
    getLatestValues(const std::tuple<ObservedObject<Ts>& ...>& objects, std::index_sequence<Is...>) {
        return std::make_tuple(std::get<Is>(objects).get()...);
    }

    // Helper function to call the callback function with the latest values
    template<std::size_t... Is>
    void callCallback(const std::tuple<std::optional<Ts>...>& values, std::index_sequence<Is...>) {
        callback(std::get<Is>(values).value()...);
    }

    // Call the callback function with the latest values
    void callCallback(const std::tuple<std::optional<Ts>...>& values) {
        callCallback(values, std::index_sequence_for<Ts...>{});
    }

    Callback callback;
    std::tuple<ObservedObject<Ts>& ...> objects;
};

#endif //UOSM_DASHBOARD_COMBINELATEST_HPP
