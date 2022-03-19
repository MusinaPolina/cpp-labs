#include "shared_ptr.hpp"
#include "matrix.hpp"

shared_ptr::Strorage::Storage(Matrix *mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Strorage::~Storage() {
    delete mtx;
}

void shared_ptr::Storage::incr() {
    ref_count_++;
}

void shared_ptr::Storage::decr() {
    ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}

shared_ptr::shared_ptr(Matrix *obj = nullptr) {
    storage_ = nullptr;
    if (obj) {
        storage_ = new Storage(obj);
    }
}

shared_ptr::~shared_ptr() {
    storage_.decr();
    if (storage.getCounter() == 0) {
        delete storage_;
    }
}

shared_ptr::shared_ptr(const shared_ptr& other): shared_ptr(nullptr) {
    if (other.storage_) {
        storage_ = other.storage_;
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
    return (shared_ == nullptr);
}

void reset(Matrix* obj = nullptr) {
    if (storage_) {
        storage_->decr();
    }
    storage_ = nullptr;
    if (obj) {
        storage_ = new Storage(obj);
    }
}

Matrix* operator->() const {
    if (storage_) {
        return storage_->getObject();
    }
    return nullptr;
}

Matrix&  operator*() const {
    assert(storage_ != nullptr);
    return *storage_->getObject();
}