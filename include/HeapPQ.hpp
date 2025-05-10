#ifndef HEAP_PQ_HPP
#define HEAP_PQ_HPP

#include "DynArray.hpp"   // nasza tablica dynamiczna
#include <stdexcept>

using namespace std;

struct Node;   // informujemy kompilator, że taki typ istnieje

// HeapPQ – kolejka priorytetowa MAX oparta na kopcu i interfejs zgodny z ArrayPQ (wersje bool + wersja zwracająca)

class HeapPQ {
public:
    HeapPQ();                                 // pusty kopiec

    // operacje podstawowe
    void  insert(const Node& n);              // dodaj
    Node  extractMax();                       // zwróć max (daje wyjątek gdy pusto)
    bool  extractMax(Node& out);              // wersja 'bool' – zgodna z ArrayPQ

    const Node& findMax() const;              // peek (daje wyjątek gdy pusto)
    bool        findMax(Node& out) const;     // wersja 'bool'

    // modify-key
    bool increaseKey(size_t idx, int newPr);
    bool decreaseKey(size_t idx, int newPr);

    // info 
    size_t size()  const { return heap_.size(); }
    bool   empty() const { return heap_.empty(); }

    // dostęp do elementu 
    Node&       operator[](size_t i)       { return heap_[i]; }
    const Node& operator[](size_t i) const { return heap_[i]; }

private:
    DynArray<Node> heap_;      // faktyczna tablica kopca
    long nextSerial_; // rosnący licznik FIFO

    // porównanie: wyższy priorytet, a przy remisie mniejszy serial 
    static bool isBetter(const Node& a, const Node& b);

    // klasyczne procedury naprawy kopca 
    void siftUp(size_t i);
    void siftDown(size_t i);
};

#endif // HEAP_PQ_HPP
