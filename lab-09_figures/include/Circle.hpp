#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const char* label);

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

    char* get_name() const;

private:
    int radius;
    const char* label;
};
