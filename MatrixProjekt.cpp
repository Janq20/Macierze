#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
#include "matrix.cpp"
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    try {
        cout << "--- TEST 1: Dodawanie macierzy (A + B) ---" << endl;
        int t1[] = { 1, 2, 3, 4 };
        int t2[] = { 10, 10, 20, 20 };

        matrix mA(2, t1);
        matrix mB(2, t2);

        cout << "Macierz A:\n" << mA;
        cout << "Macierz B:\n" << mB;

        mA + mB;
        cout << "Wynik A + B:\n" << mA;


        cout << "--- TEST 2: Mnozenie macierzy (A * A) ---" << endl;
        int tX[] = { 1, 2, 3, 4 };
        matrix mX(2, tX);
        matrix mKopia = mX;

        cout << "Macierz X:\n" << mX;

        mX* mKopia;
        cout << "Wynik X * X (powinno byc 7, 10, 15, 22):\n" << mX;

    }
    catch (const exception& e) {
        cerr << "WYJATEK: " << e.what() << endl;
    }

    return 0;
}