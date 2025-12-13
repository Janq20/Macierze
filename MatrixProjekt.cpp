#include <iostream>
#include "matrix.h"

int main() {
    // Test 1: matrix()
    matrix m1; 

    // Test 2: matrix(n)
    matrix m2(3); 

    // Test 3: matrix(n, int* t)
    int tab[] = {10, 20, 30, 40};
    matrix m3(4, tab); 
    
    // Test 4: matrix(n, int* t) z n=2
    matrix m4(2, tab); 

    std::cout << "Matrix project: all ctors OK\n";
    
    // Przykład użycia funkcji pomocniczej (dla m3)
    // m3.require_in_bounds(3); // OK
    // m3.require_in_bounds(4); // Wyświetli błąd

    return 0;
}