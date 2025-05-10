// HeapPQ.cpp – implementacja kopca kompatybilnego z ArrayPQ
#include "ArrayPQ.hpp"  // daje pełną definicję Node
#include "HeapPQ.hpp"

using namespace std;

//konstruktor 
HeapPQ::HeapPQ() : nextSerial_(0) {}

//insert 
void HeapPQ::insert(const Node& n)
{
    Node tmp = n;
    tmp.serial = nextSerial_++;
    heap_.push_back(tmp);
    siftUp(heap_.size() - 1);
}

//extract‑max
Node HeapPQ::extractMax()
{
    if (heap_.empty())
        throw runtime_error("Kolejka jest pusta");
    Node out; extractMax(out); return out;
}

bool HeapPQ::extractMax(Node& out)
{
    if (heap_.empty()) return false;

    out = heap_[0];
    heap_[0] = heap_[heap_.size() - 1];
    heap_.pop_back();
    if (!heap_.empty()) siftDown(0);
    return true;
}

//find‑max
const Node& HeapPQ::findMax() const
{
    if (heap_.empty())
        throw runtime_error("Kolejka jest pusta");
    return heap_[0];
}

bool HeapPQ::findMax(Node& out) const
{
    if (heap_.empty()) return false;
    out = heap_[0];
    return true;
}

//modify‑key 
bool HeapPQ::increaseKey(size_t idx, int newPr)
{
    if (idx >= heap_.size() || newPr < heap_[idx].priority)
        return false;
    heap_[idx].priority = newPr;
    siftUp(idx);
    return true;
}

bool HeapPQ::decreaseKey(size_t idx, int newPr)
{
    if (idx >= heap_.size() || newPr > heap_[idx].priority)
        return false;
    heap_[idx].priority = newPr;
    siftDown(idx);
    return true;
}

//funkcje pomocnicze 
bool HeapPQ::isBetter(const Node& a, const Node& b)
{
    if (a.priority != b.priority) return a.priority > b.priority;
    return a.serial < b.serial; // FIFO przy tym samym priorytecie
}

void HeapPQ::siftUp(size_t i)
{
    while (i > 0) {
        size_t p = (i - 1) / 2;
        if (!isBetter(heap_[i], heap_[p])) break;
        swap(heap_[i], heap_[p]);
        i = p;
    }
}

void HeapPQ::siftDown(size_t i)
{
    while (true) {
        size_t l = 2 * i + 1;
        size_t r = l + 1;
        size_t best = i;
        if (l < heap_.size() && isBetter(heap_[l], heap_[best])) best = l;
        if (r < heap_.size() && isBetter(heap_[r], heap_[best])) best = r;
        if (best == i) break;
        swap(heap_[i], heap_[best]);
        i = best;
    }
}
