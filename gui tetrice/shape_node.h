#pragma once
#include <iostream>
#include "piece.h"
using namespace std;

class shape_node
{
private:
    piece P;
    shape_node* next;//zr9a
    shape_node* next_shape;
    shape_node* next_color;
    shape_node* prev_color;
    shape_node* prev_shape;


public:
    int imp = 0;
    int icp = 0;
    int isp = 0;
    // constructur
    shape_node(piece Pi, shape_node*, shape_node*, shape_node*, shape_node*, shape_node*);

    // getters


    piece get_piece();

    shape_node* get_next();

    shape_node* get_next_shape();

    shape_node* get_next_color();

    shape_node* get_prev_color();

    shape_node* get_prev_shape();


    // setters
    void set_piece(piece v);

    void set_next(shape_node* v);

    void set_next_shape(shape_node* v);

    void set_next_color(shape_node* v);

    void set_prev_color(shape_node* v);

    void set_prev_shape(shape_node* v);
};
