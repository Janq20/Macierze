#pragma once

#include <memory> // Potrzebne dla std::unique_ptr
#include <stdexcept> // Dobrze mieć, jeśli funkcje pomocnicze będą rzucać wyjątkami

class matrix {
public:
    matrix(void);
    ~matrix(void);

private:
    // Pola prywatne
    int n_; // Liczba elementów (lub wierszy/kolumn, jeśli macierz jest kwadratowa/jednowymiarowa)
    int cap_; // Pojemność
    std::unique_ptr<int[]> data_; // Wskaźnik na dane macierzy (nazwałem go data_ zamiast unique_ptr<int[]>)

    // Funkcje pomocnicze (private helpers)
    int idx(int i) const;
    void require_allocated() const;
    void require_in_bounds(int i) const;
};