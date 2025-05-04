
//     g++ -std=c++17 -O2 src/*.cpp -Iinclude -o demo
// Program losuje kilkanaście liczb wraz z priorytetami i wstawia je
// do niesortowanej kolejki priorytetowej. Potem wyciąga je w kolejności
// malejącego priorytetu, pokazując poprawność działania wraz z zasadą FIFO.

#include <iostream>
#include <random>
#include "ArrayPQ.hpp"

int main() {
    ArrayPQ pq;

    const int N = 10;
    const int K = 5;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> valDist(1, 99);          // losowe wartości
    std::uniform_int_distribution<int> prioDist(0, K * N - 1);  // losowe priorytety

    std::cout << "Wstawiamy do kolejki (value, priority):\n";
    for (int i = 0; i < N; ++i) {
        Node n;
        n.value    = valDist(rng);
        n.priority = prioDist(rng);
        pq.insert(n);
        std::cout << "  (" << n.value << ", " << n.priority << ")\n";
    }

    std::cout << "\nWyciągamy w kolejności malejącego priorytetu (FIFO przy remisie):\n";
    while (!pq.empty()) {
        Node n = pq.extractMax();
        std::cout << "  (" << n.value << ", " << n.priority << ")\n";
    }

    return 0;
}
