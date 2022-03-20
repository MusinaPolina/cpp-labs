#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

    char* get_name() const override;

private:
    int width;
    int height;
};
