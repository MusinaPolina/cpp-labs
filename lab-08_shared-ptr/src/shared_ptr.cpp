#include <cassert>
#include "shared_ptr.hpp"
#include "matrix.hpp"

shared_ptr::Storage::Storage(Matrix *mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ref_count_++;
}

void shared_ptr::Storage::decr() {
    ref_count_--;
    if (ref_count_ == 0) {
        delete this;
    }
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}

void shared_ptr::updateStorage(shared_ptr &ptr, Matrix *obj) {
    ptr.storage_ = nullptr;
    if (obj) {
        ptr.storage_ = new shared_ptr::Storage(obj);
    }
}

shared_ptr::shared_ptr(Matrix* obj) {
    updateStorage(*this, obj);
}

shared_ptr::~shared_ptr() {
    if (storage_) {
        storage_->decr();
    }
}

shared_ptr::shared_ptr(const shared_ptr& other): shared_ptr(other.storage_) {
    if (storage_) {
        storage_->incr();
    }
}

Matrix* shared_ptr::ptr() const {
    if (storage_) {
        return storage_->getObject();
    }
    return nullptr;
}

bool shared_ptr::isNull() const {
    return (storage_ == nullptr);
}

void shared_ptr::reset(Matrix* obj) {
    if (storage_) {
        storage_->decr();
    }
    updateStorage(*this, obj);
}

Matrix* shared_ptr::operator->() const {
    if (storage_) {
        return storage_->getObject();
    }
    return nullptr;
}

Matrix& shared_ptr::operator*() const {
    assert(storage_ != nullptr);
    return *storage_->getObject();
}