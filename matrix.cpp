#include "matrix.h"
#include <iostream>
#include <algorithm> // Potrzebne dla std::fill
#include <stdexcept> // Dla lepszej obsługi błędów (np. std::invalid_argument)


matrix::matrix(void) 
    : matrix(0) // Domyślny konstruktor deleguje do konstruktora z parametrem 0
{
}

// NOWY KONSTRUKTOR: matrix(int n)
matrix::matrix(int n) 
{
    if (n < 0) {
        throw std::invalid_argument("Matrix size must be non-negative.");
    }
    
    // Używamy nowej metody do alokacji i zerowania
    allocate_exact(n);
    zero_all_cap();
}

matrix::~matrix(void) {
}

// ----------------------------------------------------
// NOWE FUNKCJE POMOCNICZE

// 1. allocate_exact(n)
void matrix::allocate_exact(int n) {
    if (n < 0) {
        // Ta walidacja jest już w konstruktorze, ale dobrze mieć ją tu też
        return; 
    }
    
    // Alokacja pamięci
    data_ = std::make_unique<int[]>(n);
    
    // Ustawienie pól
    n_ = n; 
    cap_ = n;
}

// 2. zero_all_cap()
void matrix::zero_all_cap() {
    if (cap_ > 0 && data_) {
        // Zerowanie całego zaalokowanego bloku pamięci
        // Używamy std::fill dla bezpieczeństwa i efektywności
        std::fill(data_.get(), data_.get() + cap_, 0); 
    }
}


// ----------------------------------------------------
// Istniejące funkcje pomocnicze (bez zmian)
// ...

int matrix::idx(int i) const {
    return i; 
}

void matrix::require_allocated() const {
    if (cap_ <= 0 || !data_) {
        std::cerr << "Error: Matrix not allocated or capacity is zero." << std::endl;
    }
}

void matrix::require_in_bounds(int i) const {
    if (i < 0 || i >= n_) {
        std::cerr << "Error: Index out of bounds. (Index: " << i << ", Size: " << n_ << ")" << std::endl;
    }
}