#pragma once

#include <iostream>
#include <memory>

/**
 * @class matrix
 * @brief Klasa reprezentująca kwadratową macierz liczb całkowitych.
 *
 * Macierz jest przechowywana w postaci jednowymiarowej tablicy `int`
 * zaalokowanej dynamicznie, o rozmiarze @p n x @p n.
 *
 * Klasa udostępnia:
 * - różne konstruktory (domyślny, z rozmiarem, z tablicą, kopiujący),
 * - metody do alokacji/realokacji pamięci,
 * - metody do wstawiania i odczytywania elementów,
 * - funkcje generujące różne wzorce (szachownica, przekątne itd.),
 * - operatory arytmetyczne i porównania.
 */
class matrix {
public:
    /**
     * @brief Konstruktor domyślny.
     *
     * Tworzy "pustą" macierz o rozmiarze 0 i pojemności 0.
     */
    matrix();

    /**
     * @brief Konstruktor z rozmiarem.
     *
     * Tworzy macierz @p n x @p n i alokuje pamięć.
     * Wszystkie elementy są inicjalizowane zerami.
     *
     * @param n Rozmiar macierzy (liczba wierszy i kolumn).
     * @throw std::invalid_argument jeśli @p n < 0.
     */
    matrix(int n);

    /**
     * @brief Konstruktor z rozmiarem i tablicą danych.
     *
     * Tworzy macierz @p n x @p n i kopiuje dane z tablicy @p t.
     *
     * @param n Rozmiar macierzy.
     * @param t Wskaźnik na tablicę źródłową o rozmiarze @p n * @p n.
     * @throw std::invalid_argument jeśli @p n <= 0 lub @p t == nullptr.
     */
    matrix(int n, int* t);

    /**
     * @brief Konstruktor kopiujący.
     *
     * Tworzy kopię danej macierzy @p m.
     *
     * @param m Macierz źródłowa.
     */
    matrix(const matrix& m);

    /**
     * @brief Destruktor.
     *
     * Pamięć jest zarządzana przez std::unique_ptr, więc
     * zwalnianie odbywa się automatycznie.
     */
    ~matrix();

    /**
     * @brief Operator przypisania.
     *
     * Kopiuje rozmiar i zawartość macierzy @p m.
     *
     * @param m Macierz źródłowa.
     * @return Referencja do *this.
     */
    matrix& operator=(const matrix& m);

    /**
     * @brief Alokuje lub realokuje pamięć dla macierzy.
     *
     * Jeżeli nowy rozmiar wymaga większej pamięci niż aktualna pojemność,
     * zostaje zaalokowana nowa tablica i dotychczasowa pamięć jest wymieniana.
     * Jeżeli pojemność jest wystarczająca, tylko zmienia się rozmiar @p n.
     * Nowo zaalokowana pamięć jest zerowana.
     *
     * @param n Nowy rozmiar macierzy (n x n).
     * @return Referencja do *this.
     * @throw std::invalid_argument jeśli @p n < 0.
     */
    matrix& alokuj(int n);

    /**
     * @brief Wstawia wartość do komórki (x, y).
     *
     * @param x Indeks wiersza (0 <= x < size()).
     * @param y Indeks kolumny (0 <= y < size()).
     * @param wartosc Wstawiana wartość.
     * @return Referencja do *this.
     * @throw std::out_of_range jeśli indeksy są poza zakresem.
     */
    matrix& wstaw(int x, int y, int wartosc);

    /**
     * @brief Zwraca wartość z komórki (x, y).
     *
     * @param x Indeks wiersza.
     * @param y Indeks kolumny.
     * @return Wartość w komórce (x, y).
     * @throw std::out_of_range jeśli indeksy są poza zakresem.
     */
    int pokaz(int x, int y) const;

    /**
     * @brief Zwraca aktualny rozmiar macierzy.
     *
     * @return Rozmiar (liczba wierszy/kolumn).
     */
    int size() const;

    /**
     * @brief Zwraca aktualną pojemność (liczbę zaalokowanych elementów).
     *
     * @return Pojemność tablicy danych (co najmniej @c size()*size()).
     */
    int capacity() const;

    /**
     * @brief Losowo wypełnia całą macierz.
     *
     * Każdy element przyjmuje wartość z zakresu [0, 9].
     *
     * @return Referencja do *this.
     */
    matrix& losuj();

    /**
     * @brief Losowo zmienia @p x elementów macierzy.
     *
     * W każdej iteracji losowany jest indeks i wstawiana wartość [0,9].
     *
     * @param x Liczba losowych modyfikacji.
     * @return Referencja do *this.
     */
    matrix& losuj(int x);

    /**
     * @brief Transponuje macierz.
     *
     * Zamienia wiersze z kolumnami.
     *
     * @return Referencja do *this.
     */
    matrix& dowroc();

    /**
     * @brief Wypełnia macierz wzorem szachownicy 0/1.
     *
     * Element (i, j) = (i + j) % 2.
     *
     * @return Referencja do *this.
     */
    matrix& szachownica();

    /**
     * @brief Tworzy macierz jednostkową.
     *
     * Wszystkie elementy są zerowane, a na głównej przekątnej ustawiana jest 1.
     *
     * @return Referencja do *this.
     */
    matrix& przekatna();

    /**
     * @brief Wypełnia elementy poniżej głównej przekątnej jedynkami.
     *
     * Element (i, j) = 1 jeśli i > j, w przeciwnym razie 0.
     *
     * @return Referencja do *this.
     */
    matrix& pod_przekatna();

    /**
     * @brief Wypełnia elementy powyżej głównej przekątnej jedynkami.
     *
     * Element (i, j) = 1 jeśli j > i, w przeciwnym razie 0.
     *
     * @return Referencja do *this.
     */
    matrix& nad_przekatna();

    /**
     * @brief Ustawia przekątną główną według zadanej tablicy.
     *
     * Cała macierz jest wcześniej zerowana.
     *
     * @param t Tablica długości co najmniej @c size(), zawierająca wartości przekątnej.
     * @return Referencja do *this.
     * @note Jeśli @p t == nullptr, metoda nic nie robi.
     */
    matrix& diagonalna(int* t);

    /**
     * @brief Ustawia przekątną przesuniętą o @p k według tablicy @p t.
     *
     * Cała macierz jest wcześniej zerowana.
     * - Jeśli @p k > 0, ustawiana jest przekątna powyżej głównej.
     * - Jeśli @p k < 0, ustawiana jest przekątna poniżej głównej.
     * - Jeśli @p k == 0, działa jak diagonalna().
     *
     * @param k Przesunięcie przekątnej względem głównej.
     * @param t Tablica wartości przekątnej (długość co najmniej size() - abs(k)).
     * @return Referencja do *this.
     * @note Jeśli @p t == nullptr, metoda nic nie robi.
     */
    matrix& diagonalna_k(int k, int* t);

    /**
     * @brief Ustawia wartości w kolumnie @p x na podstawie tablicy @p t.
     *
     * @param x Indeks kolumny (0 <= x < size()).
     * @param t Tablica o długości co najmniej @c size().
     * @return Referencja do *this.
     * @throw std::out_of_range jeśli indeks kolumny jest nieprawidłowy.
     * @note Jeśli @p t == nullptr, metoda nic nie robi.
     */
    matrix& kolumna(int x, int* t);

    /**
     * @brief Ustawia wartości w wierszu @p y na podstawie tablicy @p t.
     *
     * @param y Indeks wiersza (0 <= y < size()).
     * @param t Tablica o długości co najmniej @c size().
     * @return Referencja do *this.
     * @throw std::out_of_range jeśli indeks wiersza jest nieprawidłowy.
     * @note Jeśli @p t == nullptr, metoda nic nie robi.
     */
    matrix& wiersz(int y, int* t);

    /**
     * @brief Dodaje stałą @p a do wszystkich elementów macierzy (modyfikuje obiekt).
     *
     * @param a Dodawana wartość.
     * @return Referencja do *this.
     */
    matrix& operator+(int a);

    /**
     * @brief Odejmuje stałą @p a od wszystkich elementów macierzy (modyfikuje obiekt).
     *
     * @param a Odejmowana wartość.
     * @return Referencja do *this.
     */
    matrix& operator-(int a);

    /**
     * @brief Mnoży wszystkie elementy macierzy przez stałą @p a (modyfikuje obiekt).
     *
     * @param a Mnożnik.
     * @return Referencja do *this.
     */
    matrix& operator*(int a);

    /**
     * @brief Dodaje do macierzy inną macierz (element po elemencie).
     *
     * Operacja jest wykonywana in-place na *this.
     *
     * @param m Macierz dodawana.
     * @return Referencja do *this.
     * @throw std::invalid_argument jeśli rozmiary macierzy są różne.
     */
    matrix& operator+(const matrix& m);

    /**
     * @brief Mnożenie macierzy przez macierz.
     *
     * Wynik nadpisuje bieżącą macierz (*this).
     *
     * @param m Drugi czynnik (macierz).
     * @return Referencja do *this (zawiera wynik mnożenia).
     * @throw std::invalid_argument jeśli rozmiary macierzy są różne.
     */
    matrix& operator*(const matrix& m);

    /**
     * @brief Operator przypisania dodawania ze stałą.
     *
     * Równoważne wywołaniu @c *this + a.
     *
     * @param a Dodawana wartość.
     * @return Referencja do *this.
     */
    matrix& operator+=(int a);

    /**
     * @brief Operator przypisania odejmowania ze stałą.
     *
     * Równoważne wywołaniu @c *this - a.
     *
     * @param a Odejmowana wartość.
     * @return Referencja do *this.
     */
    matrix& operator-=(int a);

    /**
     * @brief Operator przypisania mnożenia przez stałą.
     *
     * Równoważne wywołaniu @c *this * a.
     *
     * @param a Mnożnik.
     * @return Referencja do *this.
     */
    matrix& operator*=(int a);

    /**
     * @brief Operator postinkrementacji (m++).
     *
     * Zwiększa każdy element macierzy o 1.
     *
     * @param dummy Parametr fikcyjny wymagany przez składnię postinkrementacji.
     * @return Referencja do *this (po zwiększeniu).
     */
    matrix& operator++(int dummy);

    /**
     * @brief Operator postdekrementacji (m--).
     *
     * Zmniejsza każdy element macierzy o 1.
     *
     * @param dummy Parametr fikcyjny wymagany przez składnię postdekrementacji.
     * @return Referencja do *this (po zmniejszeniu).
     */
    matrix& operator--(int dummy);

    /**
     * @brief Operator funkcyjny.
     *
     * Dodaje do każdego elementu rzutowaną na int wartość @p a.
     *
     * @param a Wartość typu double, rzutowana na int.
     * @return Referencja do *this.
     */
    matrix& operator()(double a);

    /**
     * @brief Operator porównania na równość.
     *
     * Dwie macierze są równe, jeśli mają ten sam rozmiar
     * i wszystkie odpowiadające sobie elementy są identyczne.
     *
     * @param m Macierz porównywana.
     * @return true jeśli macierze są równe, w przeciwnym razie false.
     */
    bool operator==(const matrix& m) const;

    /**
     * @brief Operator "większy niż".
     *
     * Zwraca true, jeśli wszystkie elementy @c *this są większe
     * niż odpowiadające im elementy w @p m (i rozmiary są równe).
     *
     * @param m Macierz porównywana.
     * @return true jeśli @c *this jest "większa" od @p m, w przeciwnym razie false.
     */
    bool operator>(const matrix& m) const;

    /**
     * @brief Operator "mniejszy niż".
     *
     * Zwraca true, jeśli wszystkie elementy @c *this są mniejsze
     * niż odpowiadające im elementy w @p m (i rozmiary są równe).
     *
     * @param m Macierz porównywana.
     * @return true jeśli @c *this jest "mniejsza" od @p m, w przeciwnym razie false.
     */
    bool operator<(const matrix& m) const;

    /**
     * @brief Dodawanie skalaru z lewej strony: a + m.
     *
     * Tworzy kopię macierzy @p m i dodaje do każdego elementu @p a.
     *
     * @param a Skalar.
     * @param m Macierz.
     * @return Nowa macierz zawierająca wynik dodawania.
     */
    friend matrix operator+(int a, const matrix& m);

    /**
     * @brief Odejmowanie macierzy od skalaru: a - m.
     *
     * Tworzy nową macierz o tym samym rozmiarze co @p m,
     * gdzie każdy element jest równy (a - m[i]).
     *
     * @param a Skalar.
     * @param m Macierz.
     * @return Nowa macierz zawierająca wynik odejmowania.
     */
    friend matrix operator-(int a, const matrix& m);

    /**
     * @brief Mnożenie skalaru przez macierz: a * m.
     *
     * Tworzy kopię macierzy @p m i mnoży każdy element przez @p a.
     *
     * @param a Skalar.
     * @param m Macierz.
     * @return Nowa macierz zawierająca wynik mnożenia.
     */
    friend matrix operator*(int a, const matrix& m);

    /**
     * @brief Operator strumieniowy wypisania macierzy.
     *
     * Wypisuje macierz w formacie:
     * @code
     * |    1    2 |
     * |    3    4 |
     * @endcode
     *
     * @param o Strumień wyjściowy.
     * @param m Macierz do wypisania.
     * @return Referencja do strumienia @p o.
     */
    friend std::ostream& operator<<(std::ostream& o, const matrix& m);

private:
    int n;                     ///< Aktualny rozmiar macierzy (n x n).
    int pojemnosc;             ///< Aktualna pojemność zaalokowanej tablicy (liczba elementów).
    std::unique_ptr<int[]> dane; ///< Wskaźnik na zaalokowane dane macierzy.

    /**
     * @brief Przelicza indeks dwuwymiarowy (x, y) na indeks jednowymiarowy.
     *
     * @param x Indeks wiersza.
     * @param y Indeks kolumny.
     * @return Indeks w jednowymiarowej tablicy @c dane.
     * @throw std::out_of_range jeśli indeksy są poza zakresem.
     */
    int indeks(int x, int y) const;

    /**
     * @brief Zeruje pamięć do przechowywania macierzy.
     *
     * Deklaracja pomocniczej metody; w aktualnej implementacji nie jest używana.
     *
     * @param nowy_rozmiar Docelowy rozmiar (liczba elementów).
     */
    void zeruj_pamiec(int nowy_rozmiar);
};