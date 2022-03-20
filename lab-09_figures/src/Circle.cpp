#include <iostream>
#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, std::string label): Figure(id, x, y),
    radius(radius), label(label) {};

Circle::~Circle() {
    delete label;
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

std::string Circle::get_name() const {
    return "Circle";
}