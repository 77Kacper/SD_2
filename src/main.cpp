#include <iostream>
#include <fstream>
#include <random>
#include <limits>
#include "ArrayPQ.hpp"

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
void loadFromFile(ArrayPQ& pq) {
    clearScreen();
    cout << "Podaj nazwę pliku: ";
    string filename;
    cin >> filename;

    ifstream fin(filename);
    if (!fin) {
        cout << "Nie można otworzyć pliku \"" << filename << "\"\n";
        pauseProgram();
        return;
    }

    int v, p;
    size_t count = 0;
    while (fin >> v >> p) {
        pq.insert({v, p, 0});
        ++count;
    }

    cout << "Wczytano " << count << " elementów\n";
    pauseProgram();
}

// Generowanie losowych danych
void generateRandom(ArrayPQ& pq) {
    clearScreen();
    cout << "Podaj seed i liczbę elementów: ";
    unsigned seed;
    size_t N;
    if (!(cin >> seed >> N) || N == 0) {
        cout << "Błędne dane\n";
        pauseProgram();
        return;
    }

    mt19937 rng(seed);
    uniform_int_distribution<int> valDist(0, static_cast<int>(2 * N));
    uniform_int_distribution<int> prDist(0, static_cast<int>(5 * N - 1));

    for (size_t i = 0; i < N; ++i) {
        int value = valDist(rng);
        int priority = prDist(rng);
        pq.insert({value, priority, 0});
    }

    cout << "Wygenerowano i wstawiono " << N << " elementów (seed=" << seed << ")\n";
    pauseProgram();
}

// Główna funkcja main
int main()
{
    ArrayPQ pq;
    int choice;

    while (true)
    {
        clearScreen();
        cout << "--- MENU kolejki priorytetowej (tablica) ---\n"
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
            return 0;

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
