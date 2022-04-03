#pragma once

#include <cassert>
#include <algorithm>
#include "my_vector.hpp"
#include <iostream>
#include <cstring>

namespace containers {

    template<typename T>
    my_vector<T>::my_vector() {
        size_ = 0;
        capacity_ = 1;
        array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
    }

    static std::size_t round_to_power_of_2(std::size_t n) {
        std::size_t p = 0;
        while ((1 << p) < n) {
            p++;
        }
        return (1 << p);
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) {
        capacity_ = round_to_power_of_2(n);
        size_ = n;
        array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
        for (std::size_t i = 0; i < size_; i++) {
            new(&array_[i]) T();
        }
    }

    template<typename T>
    my_vector<T>::my_vector(my_vector const &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
        for (std::size_t i = 0; i < size_; i++) {
            new(&array_[i]) T(other.array_[i]);
        }
    }

    template<typename T>
    my_vector<T> & my_vector<T>::operator=(my_vector other) {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(array_, other.array_);
        return *this;
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        this->clear();
        delete[] reinterpret_cast<char * >(array_);
    }

    template<typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() const {
        return size_ == 0;
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        reserve(n);
        for (std::size_t i = size_; i < n; i++) {
            new(&array_[i]) T();
        }
        size_ = n;
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t n) {
        std::size_t new_capacity = round_to_power_of_2(n);
        if (new_capacity <= capacity_) {
            return;
        }
        capacity_ = new_capacity;
        T* copy = reinterpret_cast<T *>(new char[sizeof(T) * capacity_]);
        for (std::size_t i = 0; i < size_; i++) {
            new(&copy[i]) T(array_[i]);
            array_[i].~T();
        }
        delete[] reinterpret_cast<char * >(array_);
        array_ = copy;
    }

    template<typename T>
    T & my_vector<T>::operator[](std::size_t index) {
        return array_[index];
    }

    template<typename T>
    T const & my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }

    template<typename T>
    void my_vector<T>::push_back(T t) {
        if (size_ == capacity_) {
            reserve(capacity_ * 2);
        }
        assert(size_ < capacity_);
        new(&array_[size_++]) T(t);
    }

    template<typename T>
    void my_vector<T>:: pop_back() {
        assert(size_);
        array_[--size_].~T();
    }

    template<typename T>
    void my_vector<T>::clear() {
        for (std::size_t i = 0; i < size_; i++) {
            array_[i].~T();
        }
        size_ = 0;
    }

    template<typename T>
    std::ostream & operator<<(std::ostream &os, const my_vector<T> &v) {
        if (v.size_) {
            os << v.array_[0];
        }
        for (std::size_t i = 1; i < v.size_; i++) {
            os << ' ';
            os << v.array_[i];
        }
        return os;
    }
}