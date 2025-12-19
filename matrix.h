#pragma once

#include <iostream>
#include <memory>

class matrix {
public:
    // --- Konstruktory i Destruktor ---
    matrix();
    matrix(int n);
    matrix(int n, int* t);
    matrix(const matrix& m);
    ~matrix();

    // --- Zarzadzanie pamiecia ---
    matrix& alokuj(int n);

    // --- Metody operacyjne (Podstawowe) ---
    matrix& wstaw(int x, int y, int wartosc);
    int pokaz(int x, int y) const;
    int size() const;

    // --- Metody Losujace ---
    matrix& losuj();          
    matrix& losuj(int x);     

    // --- Algorytmy Wypelniajace i Transpozycja ---
    matrix& dowroc();                       
    matrix& szachownica();                 
    
    matrix& przekatna();                   
    matrix& pod_przekatna();               
    matrix& nad_przekatna();               
    
    matrix& diagonalna(int* t);            
    matrix& diagonalna_k(int k, int* t);    
    
    matrix& kolumna(int x, int* t);        
    matrix& wiersz(int y, int* t);         

    // --- Operatory Matematyczne (Skalarne: Macierz dzialanie Liczba) ---
    matrix& operator+(int a);
    matrix& operator-(int a);
    matrix& operator*(int a);

    // --- Operatory Matematyczne (Macierzowe: Macierz dzialanie Macierz) ---
    matrix& operator+(const matrix& m);
    matrix& operator*(const matrix& m);

    // ---  Operatory Przypisania Zlozonego ---
    matrix& operator+=(int a);
    matrix& operator-=(int a);
    matrix& operator*=(int a);

    // ---  Inkrementacja i Dekrementacja ---
    matrix& operator++(int); // A++
    matrix& operator--(int); // A--

    // ---  Operator Funkcyjny ---
    matrix& operator()(double a); 

    // ---  Operatory Logiczne (Porownania) ---
    bool operator==(const matrix& m) const;
    bool operator>(const matrix& m) const;
    bool operator<(const matrix& m) const;

    // ---  Funkcje Zaprzyjaznione (Liczba dzialanie Macierz) ---
    friend matrix operator+(int a, const matrix& m);
    friend matrix operator-(int a, const matrix& m);
    friend matrix operator*(int a, const matrix& m);

    // --- Wypisywanie ---
    friend std::ostream& operator<<(std::ostream& o, const matrix& m);

private:
    int n;                          
    std::unique_ptr<int[]> dane;   

    int indeks(int x, int y) const;
};
