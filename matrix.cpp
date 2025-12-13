#include "matrix.h"
#include <iostream>

matrix::matrix(void) 
    : n_(0), 
      cap_(0), 
      data_(nullptr) 
{
}

matrix::~matrix(void) {
}

int matrix::idx(int i) const {
    return i; 
}

void matrix::require_allocated() const {
    if (cap_ <= 0 || !data_) {
        std::cerr << "Error: Matrix not allocated or capacity is zero." << std::endl;
    }
}

void matrix::require_in_bounds(int i) const {
    if (i < 0 || i >= n_) {
        std::cerr << "Error: Index out of bounds. (Index: " << i << ", Size: " << n_ << ")" << std::endl;
    }
}