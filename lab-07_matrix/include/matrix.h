#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);

    Matrix(Matrix const &m);

    ~Matrix();

    std::size_t get_rows() const;

    std::size_t get_cols() const;

    void set(std::size_t i, std::size_t j, int val);

    int get(std::size_t i, std::size_t j) const;

    void print(FILE *f) const;

    Matrix operator+(Matrix m) const;

    Matrix operator-(Matrix m) const;

    Matrix operator*(Matrix const &m) const;

    Matrix &operator+=(Matrix const &m);

    Matrix &operator-=(Matrix const &m);

    Matrix &operator*=(Matrix const &m);

    Matrix &operator=(Matrix m) {
        std::swap(_rows, m._rows);
        std::swap(_cols, m._cols);
        std::swap(_data, m._data);
        return *this;
    }

    bool operator==(Matrix const &m) const;

    bool operator!=(Matrix const &m) const;

private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};
#endif
