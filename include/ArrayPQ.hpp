#ifndef ARRAYPQ_HPP
#define ARRAYPQ_HPP

/*
Kryterium porównania:
    - wyższy priority >  niższy priority
    - przy równym priority wygrywa mniejszy serial (FIFO)
 */

#include "DynArray.hpp"
#include <cstddef>      // size_t
#include <stdexcept>    // runtime_error
#include <cstdint>      // int64_t

struct Node {
    int         value;      // – dana, liczba
    int         priority;   // – klucz porównania (im większy, tym ważniejszy)
    std::int64_t serial;    // – numer kolejny wstawienia (do FIFO przy remisie priorytetów)
};

class ArrayPQ {
public:
    ArrayPQ() = default;

    void insert(Node n) {
        n.serial = nextSerial_++;
        a_.push_back(n);
    }

    Node extractMax() {
        if (a_.empty()) throw std::runtime_error("ArrayPQ::extractMax – pq is empty");
        std::size_t maxIdx = findMaxIndex();
        Node maxNode = a_[maxIdx];
        a_[maxIdx] = a_[a_.size() - 1];
        a_.pop_back();               
        return maxNode;
    }

    // Zwraca węzeł o najwyższym priorytecie
    Node findMax() const {
        if (a_.empty()) throw std::runtime_error("ArrayPQ::findMax – pq is empty");
        return a_[findMaxIndex()];
    }

    //Zwiększa priorytet elementu o indeksie idx i (k opcjonalnie) aktualizuje serial, ale serial zostaje zachowujemy kolejność FIFO w ramach podniesienia klucza
    void increaseKey(std::size_t idx, int newPriority) {
        a_[idx].priority = newPriority;
    }

    std::size_t size()  const { return a_.size(); }
    bool        empty() const { return a_.empty(); }

private:
    DynArray<Node> a_;
    static std::int64_t nextSerial_;     // globalny licznik wstawek

    //Zwraca indeks pierwszego węzła o maksymalnym priorytecie Jeśli kilka ma ten sam priorytet, wybiera najstarszy (najmniejszy serial)
    std::size_t findMaxIndex() const {
        std::size_t best = 0;
        for (std::size_t i = 1; i < a_.size(); ++i) {
            if (isBetter(a_[i], a_[best])) best = i;
        }
        return best;
    }

    static bool isBetter(const Node& lhs, const Node& rhs) {
        if (lhs.priority != rhs.priority) return lhs.priority > rhs.priority;
        return lhs.serial < rhs.serial;
    }
};

inline std::int64_t ArrayPQ::nextSerial_ = 0;

#endif // ARRAYPQ_HPP
