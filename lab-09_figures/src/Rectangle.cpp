#include <iostream>
#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height): Figure(id, x, y),
    width(width), height(height) {};

void Rectangle::print() const {
    Figure::print();
    std::cout << " width = " << width << " height = " << height << std::endl;
}

bool Rectangle::is_inside(int x_point, int y_point) const {
    return std::abs(x - x_point) * 2 <= width && std::abs(y - y_point) * 2 <= height;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}

char* Rectangle::get_name() const {
    return "Rectangle";
}