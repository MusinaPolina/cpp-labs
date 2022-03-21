#include <cassert>
#include <iostream>
#include "matrix.hpp"

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int *[_rows];
    for (int _r = 0; _r < _rows; _r++) {
        _data[_r] = new int[_cols]();
    }
}

Matrix::Matrix(Matrix const &m): Matrix(m._rows, m._cols) {
    for (int _r = 0; _r < _rows; _r++) {
        for (int _c = 0; _c < _cols; _c++) {
            _data[_r][_c] = m._data[_r][_c];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < _rows; i++) {
        delete[] _data[i];
    }
    delete[] _data;
}

std::size_t Matrix::get_rows() const { return _rows; }

std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}


bool Matrix::operator==(Matrix const &m) const {
    if (_rows != m._rows || _cols != m._cols) {
        return false;
    }
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            if (_data[r][c] != m._data[r][c]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(Matrix const &m) const {
    return !(*this == m);
}
