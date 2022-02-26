#include "my_vector.hpp"
#include <cassert>
#include <algorithm>

using std::size_t;

MyVector::MyVector() : MyVector(2) {}

MyVector::MyVector(size_t init_capacity) {
    _size = 0;
    _capacity = init_capacity;
    _data = new int[_capacity];
}

MyVector::~MyVector() {
    delete[] _data;
}

void MyVector::set(size_t index, int value) {
    assert(index < _size);
    _data[index] = value;
}

int MyVector::get(size_t index) {
    assert(index < _size);
    return _data[index];
}

size_t MyVector::size() {
    return _size;
}

size_t MyVector::capacity() {
    return _capacity;
}

void MyVector::reserve(size_t new_capacity) {
    if (_capacity >= new_capacity) {
        return;
    }
    int * new_data = new int[new_capacity];
    assert(_size <= _capacity);

    for (int i = 0; i < _size; i++) {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;

    _capacity = new_capacity;
}

void MyVector::resize(size_t new_size) {
    if (new_size > _capacity) {
        MyVector::reserve(std::max(new_size, _capacity * 2));
    }
    for (size_t i = _size; i < new_size; i++) {
        _data[i] = 0;
    }
    _size = new_size;
}

void MyVector::push_back(int value) {
    assert(_size <= _capacity);
    if (_size == _capacity) {
        _capacity *= 2;
        reserve(_capacity);
    }
    _data[_size++] = value;
}

void MyVector::insert(size_t index, int value) {
    assert(index <= _size);
    push_back(value);
    for (size_t i = _size - 1; i > index; i--) {
        std::swap(_data[i], _data[i - 1]);
    }
}

void MyVector::erase(size_t index) {
    assert(index < _size);
    for (size_t i = index; i < _size - 1; i++) {
        std::swap(_data[i], _data[i + 1]);
    }
    _size--;
}