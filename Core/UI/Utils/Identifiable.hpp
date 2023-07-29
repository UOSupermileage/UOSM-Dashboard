//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_IDENTIFIABLE_HPP
#define UOSM_DASHBOARD_IDENTIFIABLE_HPP

#include <cstdint>

class Identifiable {
private:
    static uint32_t nextId;
    uint32_t id;
public:
    Identifiable() : id(++nextId) {}

    virtual bool operator==(const Identifiable& other) {
        return id == other.id;
    }

    [[nodiscard]] uint32_t getId() const {
        return id;
    }

    static uint32_t getNextId() {
        return nextId;
    }
};

#endif //UOSM_DASHBOARD_IDENTIFIABLE_HPP
