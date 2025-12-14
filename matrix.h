#pragma once

#include <memory> 
#include <stdexcept> 

class matrix {
public:
    matrix(void);
    matrix(int n);
    matrix(int n, int* t);
    ~matrix(void);

    // Etap 1: indeksowanie
    int& at(int i);
    const int& at(int i) const;
    int& operator[](int i);
    int size() const;
    int capacity() const;
    void clear();

private:
    int n_;
    int cap_;
    std::unique_ptr<int[]> data_;

    void allocate_exact(int n);
    void zero_all_cap();

    int idx(int i) const;
    void require_allocated() const;
    void require_in_bounds(int i) const;
};