#pragma once
#pragma once

#include <iostream>
using namespace std;

typedef enum
{
    color_ni,
    Red,
    Green,
    Yellow,
    Blue
} shape_color;
typedef enum
{
    shape_ni,
    Cercle,
    Rhombus,
    Square,
    Triangle
} shape;
class piece
{
private:
    shape _shape;
    shape_color _color;
    float x, y;
public:
    piece();
    piece(shape s, shape_color c,float x,float y);
    piece(int shapes_count, int colors_count);
    piece(const piece& other);
    void set_shape(shape s);
    void set_color(shape_color c);
    void set_X(float x);
    void set_Y(float y);
    float get_X() const;
    float get_Y() const;
    shape get_shape() const;
    shape_color get_color() const;
    piece& operator=(const piece& other);
    void afficher() const;
    ~piece();
};

