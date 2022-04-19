#ifndef C_MATRIX_H
#define C_MATRIX_H
#include <vector>
#include <string>
#include <exception>
#include <iostream>

class MatrixException: public std::exception {
public:
    [[nodiscard]] virtual const char* what() const noexcept = 0;
};

class BadAllocException: public MatrixException {
public:
    [[nodiscard]] const char* what() const noexcept override{
        return "Unable to allocate memory.";
    }
};

class UnableOpenFileException: public MatrixException {
public:
    [[nodiscard]] const char* what() const noexcept override{
        return "LOAD: unable to open file.";
    }
};

class InvalidFileFormatException: public MatrixException {
public:
    [[nodiscard]] const char* what() const noexcept override{
        return "LOAD: invalid file format.";
    }
};

class AddException: public MatrixException {
public:
    [[nodiscard]] const char* what() const noexcept override{
        return "ADD: dimensions do not match.";
    }
};

class MulException: public MatrixException {
public:
    [[nodiscard]] const char* what() const noexcept override{
        return "MUL: #arg1.columns != #arg2.rows.";
    }
};

class AccessException: public MatrixException {
public:
    [[nodiscard]] const char* what() const noexcept override{
        return "ACCESS: bad index.";
    }
};

class Matrix {
public:
    [[maybe_unused]] explicit Matrix(size_t r = 0, size_t c = 0);
    ~Matrix() = default;

    static Matrix load(const std::string &fname);

    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

    Matrix operator+=(Matrix a);
    Matrix operator*=(const Matrix &a);
    Matrix& operator=(Matrix m);

    [[nodiscard]] size_t rows() const;
    [[nodiscard]] size_t cols() const;

    class Iterator {
    public:
        int& operator[](size_t i );
        explicit Iterator(std::vector<int>& r);
    private:
        std::vector<int>& _row;
    };

    class ConstIterator {
    public:
        int const & operator[](size_t i ) const;
        explicit ConstIterator(const std::vector<int>& r);
    private:
        const std::vector<int>& _row;
    };

    Iterator operator[](size_t i );
    ConstIterator operator[](size_t i ) const;

private:
    std::vector<std::vector<int>> data{};
};

#endif //C_MATRIX_H
