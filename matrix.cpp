#include "matrix.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @brief Konstruktor domyślny.
 *
 * Inicjalizuje pustą macierz:
 * - n = 0
 * - pojemnosc = 0
 * - dane = nullptr
 */
matrix::matrix() : n(0), pojemnosc(0), dane(nullptr) {
}

/**
 * @brief Konstruktor z rozmiarem.
 *
 * Tworzy macierz @p n x @p n i wywołuje @ref matrix::alokuj "alokuj(n)".
 *
 * @param n Rozmiar macierzy.
 * @throw std::invalid_argument jeśli @p n < 0.
 */
matrix::matrix(int n) : n(0), pojemnosc(0), dane(nullptr) {
    if (n < 0) throw invalid_argument("Rozmiar ujemny");
    alokuj(n);
}

/**
 * @brief Konstruktor z rozmiarem i tablicą danych.
 *
 * Tworzy macierz @p n x @p n oraz kopiuje @p n*n elementów z tablicy @p t.
 *
 * @param n Rozmiar macierzy.
 * @param t Wskaźnik na tablicę o rozmiarze co najmniej @p n*@p n.
 * @throw std::invalid_argument jeśli @p n <= 0 lub @p t == nullptr.
 */
matrix::matrix(int n, int* t) : n(0), pojemnosc(0), dane(nullptr) {
    if (n <= 0) throw invalid_argument("Rozmiar musi byc dodatni");
    if (t == nullptr) throw invalid_argument("Tablica zrodlowa jest null");

    alokuj(n);
    for (int i = 0; i < n * n; ++i) {
        dane[i] = t[i];
    }
}

/**
 * @brief Konstruktor kopiujący.
 *
 * Alokuje nową pamięć i kopiuje dane z macierzy @p m.
 *
 * @param m Macierz źródłowa.
 */
matrix::matrix(const matrix& m) : n(0), pojemnosc(0), dane(nullptr) {
    if (m.n > 0) {
        alokuj(m.n);
        for (int i = 0; i < n * n; ++i) {
            dane[i] = m.dane[i];
        }
    }
}

/**
 * @brief Destruktor.
 *
 * Pamięć zwalnia się automatycznie dzięki std::unique_ptr.
 */
matrix::~matrix() {
}

/**
 * @brief Operator przypisania.
 *
 * Kopiuje rozmiar i zawartość macierzy @p m do *this.
 *
 * @param m Macierz źródłowa.
 * @return Referencja do *this.
 */
matrix& matrix::operator=(const matrix& m) {
    if (this == &m) {
        return *this;
    }
    alokuj(m.n);
    for (int i = 0; i < n * n; ++i) {
        dane[i] = m.dane[i];
    }
    return *this;
}

/**
 * @brief Alokuje/realokuje pamięć dla macierzy.
 *
 * Jeżeli @p nowe_n*@p nowe_n jest większe niż aktualna pojemność,
 * alokowana jest nowa tablica (wyzerowana). W przeciwnym razie
 * tylko zmienia się rozmiar @p n.
 *
 * @param nowe_n Nowy rozmiar macierzy.
 * @return Referencja do *this.
 * @throw std::invalid_argument jeśli @p nowe_n < 0.
 */
matrix& matrix::alokuj(int nowe_n) {
    if (nowe_n < 0) throw invalid_argument("Rozmiar ujemny");

    int wymagana_pamiec = nowe_n * nowe_n;
    if (dane == nullptr || wymagana_pamiec > pojemnosc) {
        dane.reset(new int[wymagana_pamiec]());
        pojemnosc = wymagana_pamiec;
    }

    n = nowe_n;
    return *this;
}

/**
 * @brief Przelicza indeks (x, y) na indeks jednowymiarowy.
 *
 * @param x Indeks wiersza.
 * @param y Indeks kolumny.
 * @return Indeks w jednowymiarowej tablicy @c dane.
 * @throw std::out_of_range jeśli indeksy są poza zakresem 0..n-1.
 */
int matrix::indeks(int x, int y) const {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        throw out_of_range("Indeks poza zakresem");
    }
    return x * n + y;
}

/**
 * @brief Wstawia wartość do komórki (x, y).
 *
 * @param x Indeks wiersza.
 * @param y Indeks kolumny.
 * @param wartosc Wstawiana wartość.
 * @return Referencja do *this.
 * @throw std::out_of_range jeśli indeksy są nieprawidłowe.
 */
matrix& matrix::wstaw(int x, int y, int wartosc) {
    dane[indeks(x, y)] = wartosc;
    return *this;
}

/**
 * @brief Zwraca wartość w komórce (x, y).
 *
 * @param x Indeks wiersza.
 * @param y Indeks kolumny.
 * @return Wartość w danym miejscu.
 * @throw std::out_of_range jeśli indeksy są nieprawidłowe.
 */
int matrix::pokaz(int x, int y) const {
    return dane[indeks(x, y)];
}

/**
 * @brief Zwraca rozmiar macierzy.
 *
 * @return Aktualny rozmiar @c n.
 */
int matrix::size() const {
    return n;
}

/**
 * @brief Zwraca pojemność zaalokowanej tablicy.
 *
 * @return Liczba elementów, na jaką jest zaalokowana tablica @c dane.
 */
int matrix::capacity() const {
    return pojemnosc;
}

/**
 * @brief Losowo wypełnia całą macierz wartościami 0..9.
 *
 * @return Referencja do *this.
 */
matrix& matrix::losuj() {
    for (int i = 0; i < n * n; ++i) {
        dane[i] = rand() % 10;
    }
    return *this;
}

/**
 * @brief Losowo modyfikuje @p x elementów macierzy.
 *
 * W każdej iteracji losowany jest indeks i wstawiana wartość 0..9.
 *
 * @param x Liczba modyfikacji.
 * @return Referencja do *this.
 */
matrix& matrix::losuj(int x) {
    for (int k = 0; k < x; ++k) {
        int losowy_idx = rand() % (n * n);
        dane[losowy_idx] = rand() % 10;
    }
    return *this;
}

/**
 * @brief Transponuje macierz (zamienia wiersze z kolumnami).
 *
 * Tworzy pomocniczą macierz @c temp o tym samym rozmiarze
 * i przepisuje elementy na pozycje (j,i).
 *
 * @return Referencja do *this.
 */
matrix& matrix::dowroc() {
    matrix temp(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            temp.wstaw(j, i, pokaz(i, j));
        }
    }
    *this = temp;
    return *this;
}

/**
 * @brief Wypełnia macierz wzorem szachownicy.
 *
 * Element (i, j) = (i + j) % 2.
 *
 * @return Referencja do *this.
 */
matrix& matrix::szachownica() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            wstaw(i, j, (i + j) % 2);
        }
    }
    return *this;
}

/**
 * @brief Tworzy macierz jednostkową.
 *
 * Zeruje wszystkie elementy, a na głównej przekątnej ustawia 1.
 *
 * @return Referencja do *this.
 */
matrix& matrix::przekatna() {
    for (int i = 0; i < n * n; ++i) dane[i] = 0;

    for (int i = 0; i < n; ++i) {
        wstaw(i, i, 1);
    }
    return *this;
}

/**
 * @brief Ustawia elementy pod główną przekątną na 1, pozostałe na 0.
 *
 * Element (i, j) = 1, jeśli i > j, w przeciwnym razie 0.
 *
 * @return Referencja do *this.
 */
matrix& matrix::pod_przekatna() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            wstaw(i, j, (i > j ? 1 : 0));
        }
    }
    return *this;
}

/**
 * @brief Ustawia elementy nad główną przekątną na 1, pozostałe na 0.
 *
 * Element (i, j) = 1, jeśli j > i, w przeciwnym razie 0.
 *
 * @return Referencja do *this.
 */
matrix& matrix::nad_przekatna() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            wstaw(i, j, (j > i ? 1 : 0));
        }
    }
    return *this;
}

/**
 * @brief Ustawia przekątną główną zgodnie z tablicą @p t.
 *
 * Cała macierz jest wcześniej zerowana. Jeśli @p t == nullptr
 * metoda nie wykonuje żadnych zmian.
 *
 * @param t Tablica wartości przekątnej (o długości co najmniej @c n).
 * @return Referencja do *this.
 */
matrix& matrix::diagonalna(int* t) {
    if (t == nullptr) return *this;
    for (int i = 0; i < n * n; ++i) dane[i] = 0;

    for (int i = 0; i < n; ++i) wstaw(i, i, t[i]);
    return *this;
}

/**
 * @brief Ustawia przekątną przesuniętą o @p k zgodnie z tablicą @p t.
 *
 * Cała macierz jest wcześniej zerowana:
 *  - jeśli @p k >= 0, ustawiana jest przekątna powyżej (lub równa) głównej,
 *  - jeśli @p k < 0, ustawiana jest przekątna poniżej głównej.
 *
 * @param k Przesunięcie przekątnej względem głównej.
 * @param t Tablica wartości przekątnej.
 * @return Referencja do *this.
 */
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

/**
 * @brief Ustawia wartości w kolumnie @p x według tablicy @p t.
 *
 * @param x Indeks kolumny (0..n-1).
 * @param t Tablica wartości o długości co najmniej @c n.
 * @return Referencja do *this.
 * @throw std::out_of_range jeśli @p x jest poza zakresem.
 */
matrix& matrix::kolumna(int x, int* t) {
    if (t == nullptr) return *this;
    if (x < 0 || x >= n) throw out_of_range("Zly indeks kolumny");
    for (int i = 0; i < n; ++i) wstaw(i, x, t[i]);
    return *this;
}

/**
 * @brief Ustawia wartości w wierszu @p y według tablicy @p t.
 *
 * @param y Indeks wiersza (0..n-1).
 * @param t Tablica wartości o długości co najmniej @c n.
 * @return Referencja do *this.
 * @throw std::out_of_range jeśli @p y jest poza zakresem.
 */
matrix& matrix::wiersz(int y, int* t) {
    if (t == nullptr) return *this;
    if (y < 0 || y >= n) throw out_of_range("Zly indeks wiersza");
    for (int j = 0; j < n; ++j) wstaw(y, j, t[j]);
    return *this;
}

/**
 * @brief Dodaje stałą @p a do wszystkich elementów macierzy (in-place).
 *
 * @param a Dodawana wartość.
 * @return Referencja do *this.
 */
matrix& matrix::operator+(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] += a;
    return *this;
}

/**
 * @brief Odejmuje stałą @p a od wszystkich elementów macierzy (in-place).
 *
 * @param a Odejmowana wartość.
 * @return Referencja do *this.
 */
matrix& matrix::operator-(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] -= a;
    return *this;
}

/**
 * @brief Mnoży wszystkie elementy macierzy przez stałą @p a (in-place).
 *
 * @param a Mnożnik.
 * @return Referencja do *this.
 */
matrix& matrix::operator*(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] *= a;
    return *this;
}

/**
 * @brief Dodaje do macierzy inną macierz (element po elemencie, in-place).
 *
 * @param m Macierz dodawana.
 * @return Referencja do *this.
 * @throw std::invalid_argument jeśli rozmiary są różne.
 */
matrix& matrix::operator+(const matrix& m) {
    if (n != m.n) throw invalid_argument("Rozne wymiary macierzy!");
    for (int i = 0; i < n * n; ++i) dane[i] += m.dane[i];
    return *this;
}

/**
 * @brief Mnoży macierz przez inną macierz (mnożenie macierzowe, in-place).
 *
 * Wynik przechowywany jest w pomocniczej tablicy, a następnie
 * kopiowany do @c dane.
 *
 * @param m Drugi czynnik.
 * @return Referencja do *this (zawiera wynik).
 * @throw std::invalid_argument jeśli rozmiary są różne.
 */
matrix& matrix::operator*(const matrix& m) {
    if (n != m.n) throw invalid_argument("Rozne wymiary macierzy!");
    auto wynik = std::make_unique<int[]>(n * n);

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

/**
 * @brief Dodaje stałą @p a do macierzy (operator przypisania).
 *
 * Równoważne wywołaniu @ref matrix::operator+ "(a)".
 *
 * @param a Dodawana wartość.
 * @return Referencja do *this.
 */
matrix& matrix::operator+=(int a) {
    return *this + a;
}

/**
 * @brief Odejmuje stałą @p a od macierzy (operator przypisania).
 *
 * Równoważne wywołaniu @ref matrix::operator- "(a)".
 *
 * @param a Odejmowana wartość.
 * @return Referencja do *this.
 */
matrix& matrix::operator-=(int a) {
    return *this - a;
}

/**
 * @brief Mnoży macierz przez stałą @p a (operator przypisania).
 *
 * Równoważne wywołaniu @ref matrix::operator* "(a)".
 *
 * @param a Mnożnik.
 * @return Referencja do *this.
 */
matrix& matrix::operator*=(int a) {
    return *this * a;
}

/**
 * @brief Postinkrementacja (m++) – zwiększa każdy element o 1.
 *
 * @param dummy Nie używany; wymagany przez składnię postinkrementacji.
 * @return Referencja do *this po zwiększeniu elementów.
 */
matrix& matrix::operator++(int) {
    for (int i = 0; i < n * n; ++i) dane[i]++;
    return *this;
}

/**
 * @brief Postdekrementacja (m--) – zmniejsza każdy element o 1.
 *
 * @param dummy Nie używany; wymagany przez składnię postdekrementacji.
 * @return Referencja do *this po zmniejszeniu elementów.
 */
matrix& matrix::operator--(int) {
    for (int i = 0; i < n * n; ++i) dane[i]--;
    return *this;
}

/**
 * @brief Operator funkcyjny – dodaje do wszystkich elementów wartość @p a (rzutowaną na int).
 *
 * @param a Wartość typu double, rzutowana na int.
 * @return Referencja do *this.
 */
matrix& matrix::operator()(double a) {
    int val = static_cast<int>(a);
    for (int i = 0; i < n * n; ++i) dane[i] += val;
    return *this;
}

/**
 * @brief Sprawdza równość dwóch macierzy.
 *
 * Macierze są równe, jeśli rozmiary są takie same
 * i wszystkie odpowiadające sobie elementy są identyczne.
 *
 * @param m Macierz porównywana.
 * @return true jeśli macierze są równe, w przeciwnym razie false.
 */
bool matrix::operator==(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (dane[i] != m.dane[i]) return false;
    }
    return true;
}

/**
 * @brief Porównanie "większy niż".
 *
 * Zwraca true, jeśli wszystkie elementy *this są większe
 * od odpowiadających im elementów @p m, a rozmiary są równe.
 *
 * @param m Macierz porównywana.
 * @return true jeśli *this > m, w przeciwnym razie false.
 */
bool matrix::operator>(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (dane[i] <= m.dane[i]) return false;
    }
    return true;
}

/**
 * @brief Porównanie "mniejszy niż".
 *
 * Zwraca true, jeśli wszystkie elementy *this są mniejsze
 * od odpowiadających im elementów @p m, a rozmiary są równe.
 *
 * @param m Macierz porównywana.
 * @return true jeśli *this < m, w przeciwnym razie false.
 */
bool matrix::operator<(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (dane[i] >= m.dane[i]) return false;
    }
    return true;
}

/**
 * @brief Dodawanie skalaru z lewej strony: a + m.
 *
 * Tworzy kopię macierzy @p m, dodaje do niej @p a i zwraca wynik.
 *
 * @param a Skalar.
 * @param m Macierz.
 * @return Nowa macierz zawierająca wynik.
 */
matrix operator+(int a, const matrix& m) {
    matrix wynik = m;
    wynik + a;
    return wynik;
}

/**
 * @brief Mnożenie skalaru przez macierz: a * m.
 *
 * Tworzy kopię macierzy @p m, mnoży każdy element przez @p a i zwraca wynik.
 *
 * @param a Skalar.
 * @param m Macierz.
 * @return Nowa macierz zawierająca wynik.
 */
matrix operator*(int a, const matrix& m) {
    matrix wynik = m;
    wynik* a;
    return wynik;
}

/**
 * @brief Odejmowanie macierzy od skalaru: a - m.
 *
 * Tworzy nową macierz tego samego rozmiaru co @p m,
 * gdzie każdy element jest równy (a - m[i]).
 *
 * @param a Skalar.
 * @param m Macierz.
 * @return Nowa macierz zawierająca wynik.
 */
matrix operator-(int a, const matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.dane[i] = a - m.dane[i];
    }
    return wynik;
}

/**
 * @brief Wypisuje macierz na strumień w czytelnym formacie.
 *
 * Każdy wiersz ma postać:
 * @code
 * |    a    b    c |
 * @endcode
 *
 * @param o Strumień wyjściowy.
 * @param m Macierz do wypisania.
 * @return Referencja do strumienia @p o.
 */
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