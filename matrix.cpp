#include "matrix.h"
#include <iostream>
#include <algorithm> 
#include <stdexcept>

using namespace std;

matrix::matrix() : rozmiar(0), pojemnosc(0), dane(nullptr) {
}

matrix::matrix(int n) {
    if (n < 0) {
        throw invalid_argument("Rozmiar nie moze byc ujemny!");
    }
    alokuj(n);
    zeruj();
}

matrix::matrix(int n, int* t) {
    if (n < 0) throw invalid_argument("Ujemny rozmiar!");
    if (n > 0 && t == nullptr) throw invalid_argument("Tablica zrodlowa jest nullem!");

    if (n == 0) {
        rozmiar = 0;
        pojemnosc = 0;
        dane = nullptr;
        return;
    }

    alokuj(n);
    for (int i = 0; i < n; i++) {
        dane[i] = t[i];
    }
}

matrix::~matrix() {
    delete[] dane; 
}

void matrix::alokuj(int n) {
    dane = new int[n];
    rozmiar = n;
    pojemnosc = n;
}

void matrix::zeruj() {
    if (dane) {
        for (int i = 0; i < pojemnosc; i++) dane[i] = 0;
    }
}

int& matrix::at(int i) {
    sprawdz_indeks(i);
    return dane[i];
}

const int& matrix::at(int i) const {
    sprawdz_indeks(i);
    return dane[i];
}

int& matrix::operator[](int i) {
    return dane[i]; 
}

int matrix::size() const {
    return rozmiar;
}

int matrix::capacity() const {
    return pojemnosc;
}

void matrix::clear() {
    rozmiar = 0; 
}

void matrix::sprawdz_indeks(int i) const {
    if (i < 0 || i >= rozmiar) {
        cerr << "Blad: Indeks " << i << " poza zakresem (0-" << rozmiar - 1 << ")" << endl;
        throw out_of_range("Indeks poza zakresem");
    }
}