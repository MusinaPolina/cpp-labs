#include <fstream>
#include "matrix.h"


namespace Container {

    Matrix::Matrix(size_t r, size_t c) {
        data.resize(r);

        for (std::size_t i = 0; i < r; i++)
            data[i].resize(c);
    }

    static int finNumber(std::ifstream &fin) {
        int x;
        if (!(fin >> x)) throw Exception::InvalidFileFormat();
        return x;
    }

    Matrix Matrix::load(const std::string &fname) {
        std::ifstream fin;
        fin.open(fname);

        if (fin.fail()) throw Exception::UnableOpenFile();

        size_t rows = finNumber(fin), cols = finNumber(fin);
        Matrix m(rows, cols);

        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                m[r][c] = finNumber(fin);
            }
        }
        fin.close();
        return m;
    }

    std::ostream &operator<<(std::ostream &out, const Matrix &m) {
        for (size_t r = 0; r < m.rows(); r++) {
            for (size_t c = 0; c < m.cols() - 1; c++)
                out << m.data[r][c] << ' ';

            if (m.cols()) out << m.data[r][m.cols() - 1];
            out << '\n';
        }
        return out;
    }

    Matrix &Matrix::operator=(Matrix m) {
        swap(data, m.data);
        return *this;
    }

    Matrix Matrix::operator+=(Matrix a) {
        if (rows() != a.rows() || cols() != a.cols()) throw Exception::Add();

        for (size_t r = 0; r < rows(); r++)
            for (size_t c = 0; c < cols(); c++)
                data[r][c] += a.data[r][c];

        return *this;
    }

    Matrix Matrix::operator*=(const Matrix &a) {
        if (cols() != a.rows()) throw Exception::Mul();

        Matrix res(rows(), a.cols());

        for (size_t r = 0; r < res.rows(); r++) {
            for (size_t c = 0; c < res.cols(); c++) {
                res[r][c] = 0;
                for (size_t k = 0; k < cols(); k++) {
                    res[r][c] += (*this)[r][k] * a[k][c];
                }
            }
        }
        return *this = res;
    }

    size_t Matrix::rows() const {
        return data.size();
    }

    size_t Matrix::cols() const {
        return (rows() ? data.front().size() : 0);
    }

    Matrix::Iterator Matrix::operator[](size_t i) {
        if (i >= rows()) throw Exception::Access();
        return Iterator(data[i]);
    }

    Matrix::ConstIterator Matrix::operator[](size_t i) const {
        if (i >= rows()) throw Exception::Access();
        return ConstIterator(data[i]);
    }

    Matrix::Iterator::Iterator(std::vector<int> &r) : _row(r) {}

    int &Matrix::Iterator::operator[](size_t i) {
        if (i >= _row.size()) throw Exception::Access();
        return _row[i];
    }

    Matrix::ConstIterator::ConstIterator(const std::vector<int> &r) : _row(r) {}

    int const &Matrix::ConstIterator::operator[](size_t i) const {
        if (i >= _row.size()) throw Exception::Access();
        return _row[i];
    }

}