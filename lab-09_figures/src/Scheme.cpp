#include "Scheme.hpp"

using std::size_t;

Scheme::Scheme(int capacity) {
    size_ = 0;
    figures_ = new Figure* [capacity];
}

Scheme::~Scheme() {
    delete[] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[size_++] = fg;
}

static size_t index_by_id(Figure** figures_, std::size_t size_, int id) {
    for (size_t i = 0; i < size_; i++) {
        if (figures_[i]->get_id() == id) {
            return i;
        }
    }
    return size_;
}

void Scheme::remove_figure(int id) {
    size_t ind = index_by_id(figures_, size_, id);
    delete figures_[ind];
    for (size_t i = ind + 1; i < size_; i++) {
        figures_[i - 1] = figures_[i];
    }
    if (ind != size_) {
        size_--;
    }
}

void Scheme::print_all_figures() {
    for (size_t i = 0; i < size_; i++) {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    size_t ind = index_by_id(figures_, size_, id);
    if (ind < size_) {
        figures_[ind]->zoom(factor);
    }
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for (size_t i = 0; i < size_; i++) {
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    size_t ind = index_by_id(figures_, size_, ind);
    if (ind < size_) {
        figures_[ind]->move(new_x, new_y);
    }
}