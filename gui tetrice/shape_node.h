#pragma once
#ifndef SHAPE_NODE_H
#define SHAPE_NODE_H

// Class definition and other header contents

#endif // SHAPE_NODE_H

#include <iostream>
#include "piece.h"
using namespace std;

class shape_node
{
private:
    piece P;
    shape_node* next;
    shape_node* next_shape;
    shape_node* next_color;
    shape_node* prev_color;
    shape_node* prev_shape;

public:
    // constructur
    shape_node(piece pi, shape_node*, shape_node*, shape_node*, shape_node*, shape_node*);

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
    shape_node& operator=(const shape_node& other);
};
