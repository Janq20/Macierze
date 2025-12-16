#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
#include "matrix.cpp"
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    try {
        cout << "=== TESTY PODSTAWOWE I MATEMATYKA ===" << endl;
        matrix m1(3);
        m1.losuj();
        cout << "Macierz losowa m1:\n" << m1;

        cout << "m1 + 10:\n" << (m1 + 10);

        matrix m2 = m1; 
        cout << "m1 + m2 (dodawanie macierzy):\n" << (m1 + m2);

        cout << "\n=== TESTY ALGORYTMOW WYPELNIANIA ===" << endl;

        matrix szach(4);
        cout << "Szachownica:\n" << szach.szachownica();

        matrix trojkat(4);
        cout << "Nad przekatna:\n" << trojkat.nad_przekatna();

        matrix diag(5);
        int dane_diag[] = { 1, 2, 3, 4, 5 };
        cout << "Diagonalna przesunieta (k=1):\n" << diag.diagonalna_k(1, dane_diag);

        cout << "\n=== TEST TRANSPOZYCJI ===" << endl;
        int t[] = { 1, 2, 3, 4 }; 
        matrix mT(2, t);
        cout << "Przed transpozycja:\n" << mT;
        mT.dowroc();
        cout << "Po transpozycji:\n" << mT;

    }
    catch (const exception& e) {
        cerr << "WYJATEK: " << e.what() << endl;
    }

    return 0;
}