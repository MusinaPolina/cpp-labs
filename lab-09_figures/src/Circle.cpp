#include <iostream>
#include <cstring>
#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char* label_): Figure(id, x, y),
    radius(radius) {
    label =  new char [strlen(label_) + 1];
    strcpy(label, label_);
};

Circle::~Circle() {
    delete[] label;
}

void Circle::print() const {
    Figure::print();
    std::cout << " radius = " << radius << " label = " << label << std::endl;
}

static int square(int x) {
    return x * x;
}

bool Circle::is_inside(int x_point, int y_point) const {
    return square(x - x_point) + square(y - y_point)  <= square(radius);
}

void Circle::zoom(int factor) {
    radius *= factor;
}

const char* Circle::get_name() const {
    return "Circle";
}