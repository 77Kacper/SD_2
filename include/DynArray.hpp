#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP

#include <cstddef>   // size_t
#include <utility>   // move


template <typename T>
class DynArray {
public:
    DynArray():
        data_(new T[16]),
        sz_(0),
        cap_(16) {}

    explicit DynArray(std::size_t initialCap):
        data_(new T[initialCap]),
        sz_(0),
        cap_(initialCap) {}

    ~DynArray() {
        delete[] data_;
    }

    // Blokada kopiowanie
    DynArray(const DynArray&)            = delete;
    DynArray& operator=(const DynArray&) = delete;

    // Dodaje element na koniec tablicy
    void push_back(const T& value) {
        ensureCap();
        data_[sz_] = value;
        ++sz_;
    }

    // Usuwa ostatni element
    void pop_back() {
        if (sz_ > 0) {
            --sz_;
        }
    }

    // Usuwa wszystkie elementy, nie zwalniając pamięci
    void clear() {
        sz_ = 0;
    }

    // Dostęp zapisywalny
    T& operator[](std::size_t idx) {
        return data_[idx];
    }

    // Dostęp tylko‑do‑odczytu
    const T& operator[](std::size_t idx) const {
        return data_[idx];
    }

    std::size_t size() const {
        return sz_;
    }

    std::size_t capacity() const {
        return cap_;
    }

    bool empty() const {
        return sz_ == 0;
    }

    void ensureCap() {
        if (sz_ < cap_) {
            return;
        }
        grow();
    }

private:
    void grow() {
        std::size_t newCap = cap_ + cap_ / 2;
        if (newCap == cap_) {
            ++newCap;
        }

        // Alokacja nowego bloku
        T* newData = new T[newCap];

        // Przeniesienie / skopiowanie istniejących elementów
        for (std::size_t i = 0; i < sz_; ++i) {
            newData[i] = std::move(data_[i]);
        }

        // Zwolnij stary blok i podmień wskaźnik
        delete[] data_;
        data_ = newData;
        cap_  = newCap;
    }

    T*          data_;
    std::size_t sz_;
    std::size_t cap_;
};

#endif