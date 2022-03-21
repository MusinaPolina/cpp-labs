#pragma once
#include "string"

class Figure {
public:
    Figure(int id, int x, int y);
    virtual ~Figure();

    virtual void print() const = 0;
    virtual bool is_inside(int x, int y) const = 0;
    virtual void zoom(int factor) = 0;
    void move(int new_x, int new_y);

    int get_id() const;
    virtual const char* get_name() const = 0;

protected:
    int id;
    int x;
    int y;
};
