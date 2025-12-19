#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
#include "matrix.cpp"

using namespace std;

/**
 * @brief Program testujący klasę matrix.
 *
 * Wykonywane są następujące testy:
 *  - alokacja i realokacja (zmiana rozmiaru) macierzy,
 *  - podstawowe operacje losowania i wzorców,
 *  - operatory arytmetyczne i macierzowe,
 *  - generowanie przekątnych,
 *  - test wydajności/rozmiaru dla macierzy 30x30.
 */
int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    try {
        cout << "=== TEST 1: Alokacja i podstawy ===" << endl;
        matrix m1(3);
        m1.losuj();
        cout << "M1 (3x3 losowa):\n" << m1;
        cout << "Realokacja M1 na 4x4:" << endl;
        m1.alokuj(4);
        m1.szachownica();
        cout << m1;
        cout << "Pojemnosc po alokacji 4x4: " << m1.capacity() << endl;

        cout << "Realokacja M1 na 2x2:" << endl;
        m1.alokuj(2);
        m1.losuj();
        cout << m1;
        cout << "Pojemnosc po zmianie na 2x2: " << m1.capacity() << endl;

        cout << "\n=== TEST 2: Operatory ===" << endl;
        matrix A(2);
        A.wstaw(0, 0, 1); A.wstaw(0, 1, 2);
        A.wstaw(1, 0, 3); A.wstaw(1, 1, 4);

        cout << "Macierz A:\n" << A;
        cout << "A + 10:\n" << (A + 10);
        cout << "10 - A (friend):\n" << (10 - A);

        matrix B = A;
        cout << "A * B:\n" << (A * B);

        cout << "\n=== TEST 3: Wzorce ===" << endl;
        matrix W(5);
        int dane_diag[] = { 9, 9, 9, 9, 9 };
        cout << "Diagonalna k=1:\n" << W.diagonalna_k(1, dane_diag);

        cout << "\n=== TEST 4: Duza macierz ===" << endl;
        int duze_n = 30;
        matrix Big(duze_n);
        Big.szachownica();
        cout << "Stworzono macierz 30x30 i wypelniono szachownica." << endl;
        cout << "Element [0][0]: " << Big.pokaz(0, 0) << endl;
        cout << "Element [0][1]: " << Big.pokaz(0, 1) << endl;
        cout << "Element [29][29]: " << Big.pokaz(29, 29) << endl;
        Big += 1;
        cout << "Po dodaniu 1, Element [0][1]: " << Big.pokaz(0, 1) << endl;

        if (Big.size() == 30) cout << "TEST DUZEJ MACIERZY ZALICZONY." << endl;

    }
    catch (const exception& e) {
        cerr << "WYJATEK: " << e.what() << endl;
    }

    return 0;
}