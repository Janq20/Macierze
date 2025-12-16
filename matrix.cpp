#include "matrix.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <cstdlib> 
#include <ctime>   

using namespace std;

// --- Konstruktory ---

matrix::matrix() : n(0), dane(nullptr) {
}

matrix::matrix(int n) : n(0), dane(nullptr) {
    if (n < 0) throw invalid_argument("Rozmiar ujemny");
    alokuj(n);
}

matrix::matrix(int n, int* t) : n(0), dane(nullptr) {
    if (n <= 0) throw invalid_argument("Rozmiar musi byc dodatni");
    if (t == nullptr) throw invalid_argument("Tablica zrodlowa jest null");

    alokuj(n);
    for (int i = 0; i < n * n; ++i) {
        dane[i] = t[i];
    }
}

matrix::matrix(const matrix& m) : n(0), dane(nullptr) {
    if (m.n > 0) {
        alokuj(m.n);
        for (int i = 0; i < n * n; ++i) {
            dane[i] = m.dane[i];
        }
    }
}

matrix::~matrix() {
}

// --- Metody pomocnicze ---

matrix& matrix::alokuj(int nowe_n) {
    if (nowe_n < 0) throw invalid_argument("Rozmiar ujemny");

    if (n != nowe_n) {
        n = nowe_n;
        if (n > 0) {
            dane.reset(new int[n * n]()); 
        }
        else {
            dane.reset();
        }
    }
    return *this;
}

int matrix::indeks(int x, int y) const {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        throw out_of_range("Indeks poza zakresem");
    }
    return x * n + y;
}

matrix& matrix::wstaw(int x, int y, int wartosc) {
    dane[indeks(x, y)] = wartosc;
    return *this;
}

int matrix::pokaz(int x, int y) const {
    return dane[indeks(x, y)];
}

int matrix::size() const {
    return n;
}

// --- Losowanie ---

matrix& matrix::losuj() {
    for (int i = 0; i < n * n; ++i) {
        dane[i] = rand() % 10;
    }
    return *this;
}

matrix& matrix::losuj(int x) {
    for (int k = 0; k < x; ++k) {
        int losowy_idx = rand() % (n * n);
        dane[losowy_idx] = rand() % 10;
    }
    return *this;
}

// ---  Operatory matematyczne (skalarne) ---

matrix& matrix::operator+(int a) {
    for (int i = 0; i < n * n; ++i) {
        dane[i] += a;
    }
    return *this;
}

matrix& matrix::operator-(int a) {
    for (int i = 0; i < n * n; ++i) {
        dane[i] -= a;
    }
    return *this;
}

matrix& matrix::operator*(int a) {
    for (int i = 0; i < n * n; ++i) {
        dane[i] *= a;
    }
    return *this;
}

// --- Operator wypisywania ---

ostream& operator<<(ostream& o, const matrix& m) {
    for (int i = 0; i < m.n; ++i) {
        o << "| ";
        for (int j = 0; j < m.n; ++j) {
            o << setw(4) << m.pokaz(i, j) << " ";
        }
        o << "|" << endl;
    }
    return o;
}