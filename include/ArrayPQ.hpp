#ifndef ARRAY_PQ_HPP
#define ARRAY_PQ_HPP

#include "DynArray.hpp"
#include <iostream>

struct Node {
    int  value;
    int  priority;
    long serial;
};

class ArrayPQ {
public:
    ArrayPQ() {
        nextSerial = 0;
    }

    void insert(Node n) {
        n.serial = nextSerial;
        nextSerial++;

        data.push_back(n);
    }

    bool extractMax(Node& result) {
        if (data.size() == 0) {
            return false;
        }

        size_t index = findMaxIndex();

        result = data[index];

        data[index] = data[data.size() - 1];
        data.pop_back();

        return true;
    }

    bool findMax(Node& result) const {
        if (data.size() == 0) {
            return false;
        }

        size_t index = findMaxIndex();
        result = data[index];

        return true;
    }

    bool increaseKey(size_t index, int newPriority) {
        if (index >= data.size()) {
            return false;
        }

        if (newPriority < data[index].priority) {
            return false;
        }

        data[index].priority = newPriority;
        return true;
    }

    bool decreaseKey(size_t index, int newPriority) {
        if (index >= data.size()) {
            return false;
        }

        if (newPriority > data[index].priority) {
            return false;
        }

        data[index].priority = newPriority;
        return true;
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.size() == 0;
    }

    Node& operator[](size_t i) {
        return data[i];
    }

    const Node& operator[](size_t i) const {
        return data[i];
    }

private:
    size_t findMaxIndex() const {
        size_t best = 0;

        for (size_t i = 1; i < data.size(); i++) {
            bool lepszyPriorytet = data[i].priority > data[best].priority;
            bool rownyPriorytet  = data[i].priority == data[best].priority;
            bool mniejszySerial  = data[i].serial < data[best].serial;

            if (lepszyPriorytet || (rownyPriorytet && mniejszySerial)) {
                best = i;
            }
        }

        return best;
    }

    DynArray<Node> data;
    long nextSerial;
};

#endif
