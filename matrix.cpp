#include "matrix.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @brief Konstruktor domyœlny.
 *
 * Inicjalizuje pust¹ macierz:
 * - n = 0
 * - pojemnosc = 0
 * - dane = nullptr
 */
matrix::matrix() : n(0), pojemnosc(0), dane(nullptr) {
}

/**
 * @brief Konstruktor z rozmiarem.
 *
 * Tworzy macierz @p n x @p n i wywo³uje @ref matrix::alokuj "alokuj(n)".
 *
 * @param n Rozmiar macierzy.
 * @throw std::invalid_argument jeœli @p n < 0.
 */
matrix::matrix(int n) : n(0), pojemnosc(0), dane(nullptr) {
    if (n < 0) throw invalid_argument("Rozmiar ujemny");
    alokuj(n);
}

/**
 * @brief Konstruktor z rozmiarem i tablic¹ danych.
 *
 * Tworzy macierz @p n x @p n oraz kopiuje @p n*n elementów z tablicy @p t.
 *
 * @param n Rozmiar macierzy.
 * @param t WskaŸnik na tablicê o rozmiarze co najmniej @p n*@p n.
 * @throw std::invalid_argument jeœli @p n <= 0 lub @p t == nullptr.
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
 * @brief Konstruktor kopiuj¹cy.
 *
 * Alokuje now¹ pamiêæ i kopiuje dane z macierzy @p m.
 *
 * @param m Macierz Ÿród³owa.
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
 * Pamiêæ zwalnia siê automatycznie dziêki std::unique_ptr.
 */
matrix::~matrix() {
}

/**
 * @brief Operator przypisania.
 *
 * Kopiuje rozmiar i zawartoœæ macierzy @p m do *this.
 *
 * @param m Macierz Ÿród³owa.
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
 * @brief Alokuje/realokuje pamiêæ dla macierzy.
 *
 * Je¿eli @p nowe_n*@p nowe_n jest wiêksze ni¿ aktualna pojemnoœæ,
 * alokowana jest nowa tablica (wyzerowana). W przeciwnym razie
 * tylko zmienia siê rozmiar @p n.
 *
 * @param nowe_n Nowy rozmiar macierzy.
 * @return Referencja do *this.
 * @throw std::invalid_argument jeœli @p nowe_n < 0.
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
 * @throw std::out_of_range jeœli indeksy s¹ poza zakresem 0..n-1.
 */
int matrix::indeks(int x, int y) const {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        throw out_of_range("Indeks poza zakresem");
    }
    return x * n + y;
}

/**
 * @brief Wstawia wartoœæ do komórki (x, y).
 *
 * @param x Indeks wiersza.
 * @param y Indeks kolumny.
 * @param wartosc Wstawiana wartoœæ.
 * @return Referencja do *this.
 * @throw std::out_of_range jeœli indeksy s¹ nieprawid³owe.
 */
matrix& matrix::wstaw(int x, int y, int wartosc) {
    dane[indeks(x, y)] = wartosc;
    return *this;
}

/**
 * @brief Zwraca wartoœæ w komórce (x, y).
 *
 * @param x Indeks wiersza.
 * @param y Indeks kolumny.
 * @return Wartoœæ w danym miejscu.
 * @throw std::out_of_range jeœli indeksy s¹ nieprawid³owe.
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
 * @brief Zwraca pojemnoœæ zaalokowanej tablicy.
 *
 * @return Liczba elementów, na jak¹ jest zaalokowana tablica @c dane.
 */
int matrix::capacity() const {
    return pojemnosc;
}

/**
 * @brief Losowo wype³nia ca³¹ macierz wartoœciami 0..9.
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
 * W ka¿dej iteracji losowany jest indeks i wstawiana wartoœæ 0..9.
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
 * Tworzy pomocnicz¹ macierz @c temp o tym samym rozmiarze
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
 * @brief Wype³nia macierz wzorem szachownicy.
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
 * @brief Tworzy macierz jednostkow¹.
 *
 * Zeruje wszystkie elementy, a na g³ównej przek¹tnej ustawia 1.
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
 * @brief Ustawia elementy pod g³ówn¹ przek¹tn¹ na 1, pozosta³e na 0.
 *
 * Element (i, j) = 1, jeœli i > j, w przeciwnym razie 0.
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
 * @brief Ustawia elementy nad g³ówn¹ przek¹tn¹ na 1, pozosta³e na 0.
 *
 * Element (i, j) = 1, jeœli j > i, w przeciwnym razie 0.
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
 * @brief Ustawia przek¹tn¹ g³ówn¹ zgodnie z tablic¹ @p t.
 *
 * Ca³a macierz jest wczeœniej zerowana. Jeœli @p t == nullptr
 * metoda nie wykonuje ¿adnych zmian.
 *
 * @param t Tablica wartoœci przek¹tnej (o d³ugoœci co najmniej @c n).
 * @return Referencja do *this.
 */
matrix& matrix::diagonalna(int* t) {
    if (t == nullptr) return *this;
    for (int i = 0; i < n * n; ++i) dane[i] = 0;

    for (int i = 0; i < n; ++i) wstaw(i, i, t[i]);
    return *this;
}

/**
 * @brief Ustawia przek¹tn¹ przesuniêt¹ o @p k zgodnie z tablic¹ @p t.
 *
 * Ca³a macierz jest wczeœniej zerowana:
 *  - jeœli @p k >= 0, ustawiana jest przek¹tna powy¿ej (lub równa) g³ównej,
 *  - jeœli @p k < 0, ustawiana jest przek¹tna poni¿ej g³ównej.
 *
 * @param k Przesuniêcie przek¹tnej wzglêdem g³ównej.
 * @param t Tablica wartoœci przek¹tnej.
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
 * @brief Ustawia wartoœci w kolumnie @p x wed³ug tablicy @p t.
 *
 * @param x Indeks kolumny (0..n-1).
 * @param t Tablica wartoœci o d³ugoœci co najmniej @c n.
 * @return Referencja do *this.
 * @throw std::out_of_range jeœli @p x jest poza zakresem.
 */
matrix& matrix::kolumna(int x, int* t) {
    if (t == nullptr) return *this;
    if (x < 0 || x >= n) throw out_of_range("Zly indeks kolumny");
    for (int i = 0; i < n; ++i) wstaw(i, x, t[i]);
    return *this;
}

/**
 * @brief Ustawia wartoœci w wierszu @p y wed³ug tablicy @p t.
 *
 * @param y Indeks wiersza (0..n-1).
 * @param t Tablica wartoœci o d³ugoœci co najmniej @c n.
 * @return Referencja do *this.
 * @throw std::out_of_range jeœli @p y jest poza zakresem.
 */
matrix& matrix::wiersz(int y, int* t) {
    if (t == nullptr) return *this;
    if (y < 0 || y >= n) throw out_of_range("Zly indeks wiersza");
    for (int j = 0; j < n; ++j) wstaw(y, j, t[j]);
    return *this;
}

/**
 * @brief Dodaje sta³¹ @p a do wszystkich elementów macierzy (in-place).
 *
 * @param a Dodawana wartoœæ.
 * @return Referencja do *this.
 */
matrix& matrix::operator+(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] += a;
    return *this;
}

/**
 * @brief Odejmuje sta³¹ @p a od wszystkich elementów macierzy (in-place).
 *
 * @param a Odejmowana wartoœæ.
 * @return Referencja do *this.
 */
matrix& matrix::operator-(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] -= a;
    return *this;
}

/**
 * @brief Mno¿y wszystkie elementy macierzy przez sta³¹ @p a (in-place).
 *
 * @param a Mno¿nik.
 * @return Referencja do *this.
 */
matrix& matrix::operator*(int a) {
    for (int i = 0; i < n * n; ++i) dane[i] *= a;
    return *this;
}

/**
 * @brief Dodaje do macierzy inn¹ macierz (element po elemencie, in-place).
 *
 * @param m Macierz dodawana.
 * @return Referencja do *this.
 * @throw std::invalid_argument jeœli rozmiary s¹ ró¿ne.
 */
matrix& matrix::operator+(const matrix& m) {
    if (n != m.n) throw invalid_argument("Rozne wymiary macierzy!");
    for (int i = 0; i < n * n; ++i) dane[i] += m.dane[i];
    return *this;
}

/**
 * @brief Mno¿y macierz przez inn¹ macierz (mno¿enie macierzowe, in-place).
 *
 * Wynik przechowywany jest w pomocniczej tablicy, a nastêpnie
 * kopiowany do @c dane.
 *
 * @param m Drugi czynnik.
 * @return Referencja do *this (zawiera wynik).
 * @throw std::invalid_argument jeœli rozmiary s¹ ró¿ne.
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
 * @brief Dodaje sta³¹ @p a do macierzy (operator przypisania).
 *
 * Równowa¿ne wywo³aniu @ref matrix::operator+ "(a)".
 *
 * @param a Dodawana wartoœæ.
 * @return Referencja do *this.
 */
matrix& matrix::operator+=(int a) {
    return *this + a;
}

/**
 * @brief Odejmuje sta³¹ @p a od macierzy (operator przypisania).
 *
 * Równowa¿ne wywo³aniu @ref matrix::operator- "(a)".
 *
 * @param a Odejmowana wartoœæ.
 * @return Referencja do *this.
 */
matrix& matrix::operator-=(int a) {
    return *this - a;
}

/**
 * @brief Mno¿y macierz przez sta³¹ @p a (operator przypisania).
 *
 * Równowa¿ne wywo³aniu @ref matrix::operator* "(a)".
 *
 * @param a Mno¿nik.
 * @return Referencja do *this.
 */
matrix& matrix::operator*=(int a) {
    return *this * a;
}

/**
 * @brief Postinkrementacja (m++) – zwiêksza ka¿dy element o 1.
 *
 * @param dummy Nie u¿ywany; wymagany przez sk³adniê postinkrementacji.
 * @return Referencja do *this po zwiêkszeniu elementów.
 */
matrix& matrix::operator++(int) {
    for (int i = 0; i < n * n; ++i) dane[i]++;
    return *this;
}

/**
 * @brief Postdekrementacja (m--) – zmniejsza ka¿dy element o 1.
 *
 * @param dummy Nie u¿ywany; wymagany przez sk³adniê postdekrementacji.
 * @return Referencja do *this po zmniejszeniu elementów.
 */
matrix& matrix::operator--(int) {
    for (int i = 0; i < n * n; ++i) dane[i]--;
    return *this;
}

/**
 * @brief Operator funkcyjny – dodaje do wszystkich elementów wartoœæ @p a (rzutowan¹ na int).
 *
 * @param a Wartoœæ typu double, rzutowana na int.
 * @return Referencja do *this.
 */
matrix& matrix::operator()(double a) {
    int val = static_cast<int>(a);
    for (int i = 0; i < n * n; ++i) dane[i] += val;
    return *this;
}

/**
 * @brief Sprawdza równoœæ dwóch macierzy.
 *
 * Macierze s¹ równe, jeœli rozmiary s¹ takie same
 * i wszystkie odpowiadaj¹ce sobie elementy s¹ identyczne.
 *
 * @param m Macierz porównywana.
 * @return true jeœli macierze s¹ równe, w przeciwnym razie false.
 */
bool matrix::operator==(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (dane[i] != m.dane[i]) return false;
    }
    return true;
}

/**
 * @brief Porównanie "wiêkszy ni¿".
 *
 * Zwraca true, jeœli wszystkie elementy *this s¹ wiêksze
 * od odpowiadaj¹cych im elementów @p m, a rozmiary s¹ równe.
 *
 * @param m Macierz porównywana.
 * @return true jeœli *this > m, w przeciwnym razie false.
 */
bool matrix::operator>(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (dane[i] <= m.dane[i]) return false;
    }
    return true;
}

/**
 * @brief Porównanie "mniejszy ni¿".
 *
 * Zwraca true, jeœli wszystkie elementy *this s¹ mniejsze
 * od odpowiadaj¹cych im elementów @p m, a rozmiary s¹ równe.
 *
 * @param m Macierz porównywana.
 * @return true jeœli *this < m, w przeciwnym razie false.
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
 * Tworzy kopiê macierzy @p m, dodaje do niej @p a i zwraca wynik.
 *
 * @param a Skalar.
 * @param m Macierz.
 * @return Nowa macierz zawieraj¹ca wynik.
 */
matrix operator+(int a, const matrix& m) {
    matrix wynik = m;
    wynik + a;
    return wynik;
}

/**
 * @brief Mno¿enie skalaru przez macierz: a * m.
 *
 * Tworzy kopiê macierzy @p m, mno¿y ka¿dy element przez @p a i zwraca wynik.
 *
 * @param a Skalar.
 * @param m Macierz.
 * @return Nowa macierz zawieraj¹ca wynik.
 */
matrix operator*(int a, const matrix& m) {
    matrix wynik = m;
    wynik* a;
    return wynik;
}

/**
 * @brief Odejmowanie macierzy od skalaru: a - m.
 *
 * Tworzy now¹ macierz tego samego rozmiaru co @p m,
 * gdzie ka¿dy element jest równy (a - m[i]).
 *
 * @param a Skalar.
 * @param m Macierz.
 * @return Nowa macierz zawieraj¹ca wynik.
 */
matrix operator-(int a, const matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.dane[i] = a - m.dane[i];
    }
    return wynik;
}

/**
 * @brief Wypisuje macierz na strumieñ w czytelnym formacie.
 *
 * Ka¿dy wiersz ma postaæ:
 * @code
 * |    a    b    c |
 * @endcode
 *
 * @param o Strumieñ wyjœciowy.
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