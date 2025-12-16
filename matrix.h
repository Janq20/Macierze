#pragma once

#include <iostream>

class matrix {
public:
    matrix(); 
    matrix(int n);
    matrix(int n, int* t);
    ~matrix();

    int& at(int i);
    const int& at(int i) const;
    int& operator[](int i);
    int size() const;
    int capacity() const;
    void clear();

private:
    int rozmiar;      
    int pojemnosc;   
    int* dane;        

    void alokuj(int n);
    void zeruj();
    void sprawdz_indeks(int i) const;
};