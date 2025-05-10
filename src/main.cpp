#include <iostream>
#include <fstream>
#include <random>
#include <limits>
#include "ArrayPQ.hpp"
#include "HeapPQ.hpp"

using namespace std;

// Funkcja do znajdowania indeksu elementu o danej wartości
template <typename PQ>
size_t findIndexByValueAndPriority(const PQ& pq, int value, int priority)
{
    for (size_t i = 0; i < pq.size(); ++i)
    {
        if (pq[i].value == value && pq[i].priority == priority)
            return i;
    }

    return static_cast<size_t>(-1);
}

// Czyszczenie ekranu
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pauza – czekanie na Enter
void pauseProgram() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n### Naciśnij Enter, aby kontynuować";
    cin.get();
}

// Wczytywanie danych z pliku
template <typename PQ>
void loadFromFile(PQ& pq) {
    clearScreen();
    cout << "podaj nazwę pliku: ";
    string fn; cin >> fn;

    ifstream fin(fn);
    if (!fin) { cout << "nie można otworzyć pliku\n"; pauseProgram(); return; }

    int v, p; size_t cnt = 0;
    while (fin >> v >> p) { pq.insert({v, p, 0}); ++cnt; }

    cout << "wczytano " << cnt << " elementów\n";
    pauseProgram();
}

// Generowanie losowych danych
template <typename PQ>
void generateRandom(PQ& pq) {
    clearScreen();
    cout << "podaj seed i N: ";
    unsigned seed; size_t N;
    if (!(cin >> seed >> N) || N == 0) { cout << "błędne dane\n"; pauseProgram(); return; }

    mt19937 rng(seed);
    uniform_int_distribution<int> vDist(0, 2 * (int)N);
    uniform_int_distribution<int> pDist(0, 5 * (int)N - 1);

    for (size_t i = 0; i < N; ++i)
        pq.insert({vDist(rng), pDist(rng), 0});

    cout << "wstawiono " << N << " losowych elementów (seed=" << seed << ")\n";
    pauseProgram();
}

template <typename PQ>
void menuLoop(PQ& pq)
{
    int choice;

    while (true)
    {
        clearScreen();
        cout << "--- MENU kolejki ---\n"
             << "1  insert(e p)\n"
             << "2  extract-max()\n"
             << "3  find-max()\n"
             << "4  increase-key(e p)\n"
             << "5  decrease-key(e p)\n"
             << "6  return-size()\n"
             << "7  load-from-file\n"
             << "8  generate-random(seed N)\n"
             << "0  quit\n\n> ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "podaj cyfrę z menu";
            pauseProgram();
            continue;
        }

        switch (choice)
        {
        case 0:
            clearScreen();
            cout << "koniec\n";
            return;

        case 1:
        {
            clearScreen();
            cout << "podaj e i p: ";
            int e, p;

            if (cin >> e >> p) {
                pq.insert({e, p, 0});
                cout << "wstawiono (" << e << ", " << p << ")\n";
            } else {
                cout << "błędne dane\n";
            }

            pauseProgram();
            break;
        }

        case 2:
        {
            clearScreen();
            Node maxNode;

            if (pq.extractMax(maxNode)) {
                cout << "wyjęto (" << maxNode.value << ", " << maxNode.priority << ")\n";
            } else {
                cout << "kolejka jest pusta\n";
            }

            pauseProgram();
            break;
        }

        case 3:
        {
            clearScreen();
            Node maxNode;

            if (pq.findMax(maxNode)) {
                cout << "max = (" << maxNode.value << ", " << maxNode.priority << ")\n";
            } else {
                cout << "kolejka jest pusta\n";
            }

            pauseProgram();
            break;
        }

        case 4:
        {
        clearScreen();
            cout << "podaj e, obecny p i nowy p: ";
            int e, currentP, newP;

            if (cin >> e >> currentP >> newP)
            {
                size_t idx = findIndexByValueAndPriority(pq, e, currentP);

                if (idx == static_cast<size_t>(-1))
                {
                    cout << "nie znaleziono takiego elementu\n";
                }
                else if (pq.increaseKey(idx, newP))
                {
                    cout << "zwiększono priorytet\n";
                }
                else
                {
                    cout << "nowy priorytet musi być większy lub równy bieżącemu\n";
                }
            }
            else
            {
                cout << "błędne dane\n";
            }

            pauseProgram();
            break;
        }


        case 5:
        {
        clearScreen();
        cout << "podaj e, obecny p i nowy p: ";
        int e, currentP, newP;

        if (cin >> e >> currentP >> newP)
            {
                size_t idx = findIndexByValueAndPriority(pq, e, currentP);

                if (idx == static_cast<size_t>(-1))
                {
                    cout << "nie znaleziono takiego elementu\n";
                }
                else if (pq.decreaseKey(idx, newP))
                {
                    cout << "zmniejszono priorytet\n";
                }
                else
                {
                    cout << "nowy priorytet musi być mniejszy lub równy bieżącemu\n";
                }
            }
            else
            {
                cout << "błędne dane\n";
            }

            pauseProgram();
            break;
        }

        case 6:
        {
            clearScreen();
            cout << "rozmiar = " << pq.size() << '\n';
            pauseProgram();
            break;
        }

        case 7:
            loadFromFile(pq);
            break;

        case 8:
            generateRandom(pq);
            break;

        default:
            cout << "nieznana opcja\n";
            pauseProgram();
        }
    }
}

int main()
{
    clearScreen();
    cout << "Wybierz implementację kolejki:\n"
         << "1 – niesortowana tablica (ArrayPQ)\n"
         << "2 – kopiec binarny (HeapPQ)\n> ";

    int impl;
    if (!(cin >> impl) || (impl != 1 && impl != 2)) {
        cout << "niepoprawny wybór – koniec\n";
        return 0;
    }

    if (impl == 1) {
        ArrayPQ pq;
        menuLoop(pq);
    } else {
        HeapPQ pq;
        menuLoop(pq);
    }
}