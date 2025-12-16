#include "matrix.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <cstdlib> 
#include <ctime>  

using namespace std;

// ================= KONSTRUKTORY =================

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

// ================= ALOKACJA I POMOCNICZE =================

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

// ================= LOSOWANIE =================

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

// ================= ALGORYTMY WYPELNIANIA =================

matrix& matrix::dowroc() {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int temp = pokaz(i, j);
            wstaw(i, j, pokaz(j, i));
            wstaw(j, i, temp);
        }
    }
    return *this;
}

matrix& matrix::szachownica() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            wstaw(i, j, (i + j) % 2);
        }
    }
    return *this;
}

matrix& matrix::przekatna() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            wstaw(i, j, (i == j ? 1 : 0));
        }
    }
    return *this;
}

matrix& matrix::pod_przekatna() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            wstaw(i, j, (i > j ? 1 : 0));
        }
    }
    return *this;
}

matrix& matrix::nad_przekatna() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            wstaw(i, j, (j > i ? 1 : 0));
        }
    }
    return *this;
}

matrix& matrix::diagonalna(int* t) {
    if (t == nullptr) return *this;
    for (int i = 0; i < n * n; ++i) dane[i] = 0;
    for (int i = 0; i < n; ++i) wstaw(i, i, t[i]);
    return *this;
}

matrix& matrix::diagonalna_k(int k, int* t) {
    if (t == nullptr) return *this;
    for (int i = 0; i < n * n; ++i) dane[i] = 0;

    if (k >= 0) {
        for (int i = 0; i < n - k; ++i) wstaw(i, i + k, t[i]);
    }
    else {
        int p = -k;
        for (int i = 0; i < n - p; ++i) wstaw(i + p, i, t[i]);
    }
    return *this;
}

matrix& matrix::kolumna(int x, int* t) {
    if (t == nullptr) return *this;
    if (x < 0 || x >= n) throw out_of_range("Zly indeks kolumny");
    for (int i = 0; i < n; ++i) wstaw(i, x, t[i]);
    return *this;
}

matrix& matrix::wiersz(int y, int* t) {
    if (t == nullptr) return *this;
    if (y < 0 || y >= n) throw out_of_range("Zly indeks wiersza");
    for (int j = 0; j < n; ++j) wstaw(y, j, t[j]);
    return *this;
}

// ================= OPERATORY SKALARNE =================

matrix& matrix::operator+(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] += a;
    return *this;
}

matrix& matrix::operator-(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] -= a;
    return *this;
}

matrix& matrix::operator*(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] *= a;
    return *this;
}

// ================= OPERATORY MACIERZOWE =================

matrix& matrix::operator+(const matrix& m) {
    if (n != m.n) throw invalid_argument("Rozne wymiary macierzy przy dodawaniu!");
    for (int i = 0; i < n * n; ++i) dane[i] += m.dane[i];
    return *this;
}

matrix& matrix::operator*(const matrix& m) {
    if (n != m.n) throw invalid_argument("Rozne wymiary macierzy przy mnozeniu!");

    unique_ptr<int[]> wynik(new int[n * n]());

    for (int w = 0; w < n; ++w) {
        for (int k = 0; k < n; ++k) {
            int suma = 0;
            for (int i = 0; i < n; ++i) {
                suma += pokaz(w, i) * m.pokaz(i, k);
            }
            wynik[w * n + k] = suma;
        }
    }
    for (int i = 0; i < n * n; ++i) dane[i] = wynik[i];

    return *this;
}

// ================= WYPISYWANIE =================

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