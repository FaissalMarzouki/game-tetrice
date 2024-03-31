#include "shape_node.h"

shape_node::shape_node(piece pi, shape_node* next = NULL, shape_node* next_shape = NULL, shape_node* next_color = NULL, shape_node* prev_shape = NULL, shape_node* prev_color = NULL)
{
    this->P = pi;
    this->next = next;
    this->next_shape = next_shape;
    this->next_color = next_color;
    this->prev_shape = prev_shape;
    this->prev_color = prev_color;
}

// getters

piece shape_node::get_piece()
{
    return this->P;
}
shape_node* shape_node::get_next()
{
    return this->next;
}
shape_node* shape_node::get_next_shape()
{
    return this->next_shape;
}
shape_node* shape_node::get_next_color()
{
    return this->next_color;
}
shape_node* shape_node::get_prev_color()
{
    return this->prev_color;
}
shape_node* shape_node::get_prev_shape()
{
    return this->prev_shape;
}

// setters

void shape_node::set_piece(piece v)
{
    this->P = v;
}
void shape_node::set_next(shape_node* v)
{
    this->next = v;
}
void shape_node::set_next_shape(shape_node* v)
{
    this->next_shape = v;
}
void shape_node::set_next_color(shape_node* v)
{
    this->next_color = v;
}
void shape_node::set_prev_color(shape_node* v)
{
    this->prev_color = v;
}
void shape_node::set_prev_shape(shape_node* v)
{
    this->prev_shape = v;
}
shape_node& shape_node::operator=(const shape_node& other)
{
    if (this != &other) {
        P = other.P; // Copy piece object
        next = other.next; // Copy next pointer
        next_shape = other.next_shape; // Copy next_shape pointer
        next_color = other.next_color; // Copy next_color pointer
        prev_shape = other.prev_shape; // Copy prev_shape pointer
        prev_color = other.prev_color; // Copy prev_color pointer
    }
    return *this;
}