#include "matrix.h"
#include <iostream>

// Dla wygody w funkcjach pomocniczych
// Możesz zdefiniować własne wyjątki lub użyć standardowych, np. std::logic_error
#define ERROR_UNALLOCATED "Matrix not allocated or capacity is zero."
#define ERROR_OUT_OF_BOUNDS "Index out of bounds."

matrix::matrix(void) 
    : n_(0), cap_(0), data_(nullptr) 
{
    // Konstruktor: Inicjalizacja pól
}

matrix::~matrix(void) {
    // Destruktor: unique_ptr automatycznie zwolni pamięć,
    // więc tutaj nic nie trzeba robić, chyba że masz inne zasoby.
}

// ----------------------------------------------------
// Implementacja funkcji pomocniczych

// Zwraca indeks. Na razie niech po prostu zwraca wejście.
// W bardziej złożonym przypadku (np. 2D macierz), funkcja ta obliczałaby 1D indeks.
int matrix::idx(int i) const {
    return i; 
}

// Sprawdza, czy pamięć jest zaalokowana (cap_ > 0 i data_ nie jest nullptr)
void matrix::require_allocated() const {
    if (cap_ <= 0 || !data_) {
        // Możesz użyć wyjątków dla profesjonalnego kodu:
        // throw std::logic_error(ERROR_UNALLOCATED);
        // Na potrzeby edukacyjne możesz użyć assert lub std::cerr, 
        // ale najlepsze są wyjątki.
        std::cerr << "Error: " << ERROR_UNALLOCATED << std::endl;
        // W prawdziwym kodzie: std::terminate(); lub obsługa błędów.
    }
}

// Sprawdza, czy indeks jest w zakresie [0, n_-1]
void matrix::require_in_bounds(int i) const {
    if (i < 0 || i >= n_) {
        // Wyrzucenie wyjątku
        // throw std::out_of_range(ERROR_OUT_OF_BOUNDS);
        std::cerr << "Error: " << ERROR_OUT_OF_BOUNDS << " (Index: " << i << ", Size: " << n_ << ")" << std::endl;
    }
}