#include "matrix.h"
#include <iostream>
#include <algorithm> // Potrzebne dla std::fill i std::copy
#include <stdexcept>

// Istniejące implementacje matrix(void) i matrix(int n) bez zmian

matrix::matrix(void) 
    : matrix(0)
{
}

matrix::matrix(int n) 
{
    if (n < 0) {
        throw std::invalid_argument("Matrix size must be non-negative.");
    }
    
    allocate_exact(n);
    zero_all_cap();
}

// NOWY KONSTRUKTOR: matrix(int n, int* t)
matrix::matrix(int n, int* t)
{
    // 1. Walidacje
    if (n < 0) {
        throw std::invalid_argument("Matrix size must be non-negative.");
    }
    if (n > 0 && t == nullptr) {
        throw std::invalid_argument("Source array pointer (t) cannot be nullptr if size (n) > 0.");
    }
    
    // Jeśli rozmiar jest 0, delegujemy do konstruktora z n=0
    if (n == 0) {
        matrix(0);
        return;
    }

    // 2. Alokacja pamięci
    allocate_exact(n);

    // 3. Kopiowanie danych (używamy std::copy)
    // Kopiujemy n elementów z t do data_.get()
    std::copy(t, t + n, data_.get());
}

matrix::~matrix(void) {
}

// Pozostałe funkcje pomocnicze... (bez zmian)

void matrix::allocate_exact(int n) {
    if (n < 0) {
        return; 
    }
    
    data_ = std::make_unique<int[]>(n);
    n_ = n; 
    cap_ = n;
}

void matrix::zero_all_cap() {
    if (cap_ > 0 && data_) {
        std::fill(data_.get(), data_.get() + cap_, 0); 
    }
}

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