#pragma once

#include <memory> 
#include <stdexcept> 

class matrix {
public:
    matrix(void);
    ~matrix(void);

private:
    int n_; 
    int cap_; 
    std::unique_ptr<int[]> data_; 

    int idx(int i) const;
    void require_allocated() const;
    void require_in_bounds(int i) const;
};