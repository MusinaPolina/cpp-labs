#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const std::string &label);
    ~Circle() override = default;

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

    const char* get_name() const override;

private:
    int radius;
    std::string label;
    static const char *NAME;
};
