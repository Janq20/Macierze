#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
#include "matrix.cpp" 
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    try {
        cout << "=== TESTY PODSTAWOWE I ALGORYTMY (Stare) ===" << endl;
        matrix m1(3);
        m1.losuj();
        cout << "Macierz m1:\n" << m1;

        matrix szach(4);
        szach.szachownica();
        cout << "Szachownica:\n" << szach;

        cout << "\n=== TESTY NOWE: POROWNANIA ===" << endl;
        matrix A(2);
        matrix B(2);
        A.wstaw(0, 0, 5); B.wstaw(0, 0, 5); 
        
        if (A == B) cout << "A == B : TAK (Poprawnie)\n";
        else        cout << "A == B : NIE (Blad)\n";

        B.wstaw(0, 0, 100);
        if (B > A) cout << "B > A : TAK (Poprawnie)\n";
        else       cout << "B > A : NIE (Blad)\n";

        cout << "\n=== TESTY NOWE: OPERATORY INKREMENTACJI I FUNKCYJNE ===" << endl;
        matrix C(2);
        cout << "C przed ++ (same zera):\n" << C;
        C++; 
        cout << "C po ++ (same jedynki):\n" << C;

        C += 10;
        cout << "C po += 10 (same 11):\n" << C;

        cout << "C(2.5) - dodaje czesc calkowita (2):\n";
        C(2.5);
        cout << C; 

        cout << "\n=== TESTY NOWE: FRIEND (int - Macierz) ===" << endl;
        matrix D = 20 - C;
        cout << "Wynik 20 - C:\n" << D;

    }
    catch (const exception& e) {
        cerr << "WYJATEK: " << e.what() << endl;
    }

    return 0;
}