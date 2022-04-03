#pragma once
#include <cstddef>
#include <iosfwd>
namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();
    explicit my_vector(std::size_t n);
    my_vector(my_vector const &other);
    my_vector & operator=(my_vector other);
    ~my_vector();

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::size_t capacity() const;
    [[nodiscard]] bool empty() const;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T & operator[](std::size_t index);
    T const & operator[](std::size_t index) const;

    void push_back(T t);
    void pop_back();
    void clear();

    template<typename S>
    friend std::ostream & operator<<(std::ostream &os, const my_vector<S> &v);

private:
    size_t capacity_;
    size_t size_;
    T* array_;
};

}

#include "my_vector_impl.hpp"