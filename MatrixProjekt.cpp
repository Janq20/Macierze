#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    matrix m1;
    matrix m2(3);

    int tab[] = { 10, 20, 30, 40 };
    matrix m3(4, tab);
    matrix m4(2, tab);

    cout << "ctor tests OK\n";

    // Test indeksowania i walidacji
    m2.at(0) = 5;
    m2.at(1) = 6;
    m2[2] = 7;
    cout << "m2: " << m2.at(0) << "," << m2.at(1) << "," << m2.at(2) << "\n";
    m2.at(3); 
    cout << "size=" << m3.size() << " cap=" << m3.capacity() << "\n";

    return 0;
}