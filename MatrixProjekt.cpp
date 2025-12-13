#include <iostream>
#include "matrix.h"

int main() {
    matrix m;
    std::cout << "matrix project: init OK\n";
    
    // Testowanie funkcji pomocniczych (sprawdzą się błędy w konsoli, 
    // ponieważ macierz jest pusta i niezaalokowana)
    // m.require_allocated();
    // m.require_in_bounds(0);

    return 0;
}