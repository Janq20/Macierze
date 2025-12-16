#pragma once

#include <iostream>
#include <memory>

class matrix {
public:
    matrix();
    matrix(int n);
    matrix(int n, int* t);
    matrix(const matrix& m);
    ~matrix();

    matrix& alokuj(int n);
    matrix& wstaw(int x, int y, int wartosc);
    int pokaz(int x, int y) const;
    int size() const;

    friend std::ostream& operator<<(std::ostream& o, const matrix& m);

private:
    int n;
    std::unique_ptr<int[]> dane;

    int indeks(int x, int y) const;
};