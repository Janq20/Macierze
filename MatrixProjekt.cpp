#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    try {
        matrix m1;
        matrix m2(3);

        int tab[] = { 10, 20, 30, 40 };
        matrix m3(4, tab);

        cout << "Testy konstruktorow OK" << endl;

        m2.at(0) = 5;
        m2.at(1) = 6;
        m2[2] = 7;

        cout << "m2: " << m2.at(0) << ", " << m2.at(1) << ", " << m2.at(2) << endl;
        cout << "Rozmiar m3: " << m3.size() << " Pojemnosc: " << m3.capacity() << endl;
    }
    catch (const exception& e) {
        cerr << "Lapanie wyjatku: " << e.what() << endl;
    }

    return 0;
}