#include <iostream>
#include "matrix.h"
#include "matrix.cpp"
using namespace std;

int main() {
    try {
        matrix m1(3);
        m1.wstaw(0, 0, 10);
        m1.wstaw(1, 1, 20);
        m1.wstaw(2, 2, 30);
        m1.wstaw(0, 2, 5);

        cout << "m1:" << endl;
        cout << m1 << endl;

        int tab[] = { 1, 2, 3, 4 };
        matrix m2(2, tab);
        cout << "m2:" << endl;
        cout << m2 << endl;

        matrix m3 = m1;
        m3.wstaw(0, 0, 999);

        cout << "m3 (kopia):" << endl;
        cout << m3 << endl;

        cout << "m1 (oryginal):" << endl;
        cout << m1 << endl;

        cout << m1.pokaz(5, 5);
    }
    catch (const exception& e) {
        cerr << "Wyjatek: " << e.what() << endl;
    }

    return 0;
}