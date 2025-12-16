#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
#include "matrix.cpp"
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(NULL))); 

    try {
        cout << "--- TEST: Losowanie (calosc) ---" << endl;
        matrix m1(5);
        m1.losuj(); 
        cout << m1 << endl;

        cout << "--- TEST: Operatory matematyczne (+, -, *) ---" << endl;
        cout << "Dodaje 10:" << endl;
        m1 + 10;
        cout << m1 << endl;

        cout << "Mnoze przez 2:" << endl;
        m1 * 2;
        cout << m1 << endl;

        cout << "Odejmuje 5:" << endl;
        m1 - 5;
        cout << m1 << endl;

        cout << "--- TEST: Losowanie punktowe (3 liczby) ---" << endl;
        matrix m2(4); 
        m2.losuj(3);  
        cout << m2 << endl;

    }
    catch (const exception& e) {
        cerr << "Wyjatek: " << e.what() << endl;
    }

    return 0;
}