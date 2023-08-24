//
// Created by Jeremy Cote on 2023-08-18.
//

#ifndef UOSM_DASHBOARD_DATAQUEUE_HPP
#define UOSM_DASHBOARD_DATAQUEUE_HPP

#include <stdexcept>

#include "lvgl/lvgl.h"

/** @ingroup core-ui-utils
 *  A class that aggregates the data to display on a bar chart.
 *  It can store any type T, but the values will be cast to lv_coord_t when displayed in a bar chart.
 *  Follows FIFO model.
 */
template<typename T>
class DataQueue {
private:
    T** values;
    uint8_t head;
    uint8_t size;
public:
    explicit DataQueue(uint8_t size): size(size), head(0) {
        if (size <= 0) {
            throw std::invalid_argument("Size must be at least 1");
        }

        values = new T*[size];
    }

    /**
     * @return the max size of the collection
     */
    [[nodiscard]] uint8_t getSize() const { return size; }

    /**
     * @return the number of values stored in the collection.
     */
    [[nodiscard]] uint8_t getNumberOfElements() const { return head; }

    /**
     * Return the underlying data of the collection.
     * Use to set the data source of a bar chart.
     * @return a pointer to the underlying data source
     */
    [[nodiscard]] T** getValues() const { return values; }

    /**
     * @return a pointer to the newest value added to the collection.
     */
    [[nodiscard]] T* getLatestValue() const noexcept(false) {
        if (head == 0) {
            throw std::out_of_range("The BarDataCollection is empty.");
        }

        return values[head - 1];
    }

    /**
     * Copy a value into the bar data collection.
     * IMPORTANT: This creates a copy of the passed value.
     * @param value to copy into the collection
     */
    void add(T value) {
        if (head == size) {
            delete values[0];
            for (uint8_t i = 1; i < size; i++) {
                values[i - 1] = values[i];
            }
            head--;
        }

        values[head] = new T(value);
        head++;
    }

    /**
     * Update the last element of the collection.
     * Useful if the latest value is still changing.
     * If the collection is empty, this acts as a call to add
     * @param value
     */
    void update(T value) {
        if (head == 0) {
            add(value);
            return;
        }

        uint8_t i = head - 1;

        if (values[i] != nullptr) {
            delete values[i];
        }

        values[i] = new T(value);
    }
};

#endif //UOSM_DASHBOARD_DATAQUEUE_HPP
