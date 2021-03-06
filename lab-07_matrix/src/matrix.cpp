#include <cassert>
#include <iostream>
#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int *[_rows];
    for (int _r = 0; _r < _rows; _r++) {
        _data[_r] = new int[_cols]();
    }
}

Matrix::Matrix(Matrix const &m) : Matrix(m._rows, m._cols) {
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

void Matrix::print(FILE *f) const {
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols - 1; c++) {
            fprintf(f, "%d ", _data[r][c]);
        }
        if (_cols) {
            fprintf(f, "%d", _data[r][_cols - 1]);
        }
        fprintf(f, "\n");
    }
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

Matrix &Matrix::operator+=(Matrix const &m) {
    assert(_rows == m._rows && _cols == m._cols);
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            _data[r][c] += m._data[r][c];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(Matrix const &m) {
    assert(_rows == m._rows && _cols == m._cols);
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            _data[r][c] -= m._data[r][c];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(Matrix const &m) {
    *this = (*this * m);
    return *this;
}

Matrix Matrix::operator+(Matrix m) const {
    return m += *this;
}

Matrix Matrix::operator-(Matrix m) const {
    assert(_rows == m._rows && _cols == m._cols);
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            m._data[r][c] = _data[r][c] - m._data[r][c];
        }
    }
    return m;
}

Matrix Matrix::operator*(Matrix const &m) const {
    assert(_cols == m._rows);
    Matrix res(_rows, m._cols);
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < m._cols; c++) {
            for (int i = 0; i < _cols; i++) {
                res._data[r][c] += _data[r][i] * m._data[i][c];
            }
        }
    }
    return res;
}