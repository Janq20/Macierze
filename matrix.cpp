#include "matrix.h"
#include <iostream>
#include <algorithm> 
#include <stdexcept>

using namespace std;
matrix::matrix(void)
    : matrix(0)
{
}

matrix::matrix(int n)
{
    if (n < 0) {
        throw invalid_argument("Matrix size must be non-negative.");
    }

    allocate_exact(n);
    zero_all_cap();
}

matrix::matrix(int n, int* t)
{
    // 1. Walidacje
    if (n < 0) {
        throw invalid_argument("Matrix size must be non-negative.");
    }
    if (n > 0 && t == nullptr) {
        throw invalid_argument("Source array pointer (t) cannot be nullptr if size (n) > 0.");
    }

    if (n == 0) {
        allocate_exact(0);
        zero_all_cap();
        return;
    }

    // 2. Alokacja pamięci
    allocate_exact(n);
    copy(t, t + n, data_.get());
}

matrix::~matrix(void) {
}

void matrix::allocate_exact(int n) {
    if (n < 0) {
        return;
    }

    data_ = make_unique<int[]>(n);
    n_ = n;
    cap_ = n;
}

void matrix::zero_all_cap() {
    if (cap_ > 0 && data_) {
        fill(data_.get(), data_.get() + cap_, 0);
    }
}

int matrix::idx(int i) const {
    return i;
}

void matrix::require_allocated() const {
    if (cap_ <= 0 || !data_) {
        cerr << "Error: Matrix not allocated or capacity is zero." << endl;
    }
}

void matrix::require_in_bounds(int i) const {
    if (i < 0 || i >= n_) {
        cerr << "Error: Index out of bounds. (Index: " << i << ", Size: " << n_ << ")" << endl;
    }
}