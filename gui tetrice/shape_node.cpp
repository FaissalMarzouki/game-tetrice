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
        // Deep copy piece object
        P = other.P;

        // Deep copy next node
        if (other.next != nullptr) {
            next = new shape_node(*other.next);
        }
        else {
            next = nullptr;
        }

        // Deep copy next_shape node
        if (other.next_shape != nullptr) {
            next_shape = new shape_node(*other.next_shape);
        }
        else {
            next_shape = nullptr;
        }

        // Deep copy next_color node
        if (other.next_color != nullptr) {
            next_color = new shape_node(*other.next_color);
        }
        else {
            next_color = nullptr;
        }

        // Deep copy prev_shape node
        if (other.prev_shape != nullptr) {
            prev_shape = new shape_node(*other.prev_shape);
        }
        else {
            prev_shape = nullptr;
        }

        // Deep copy prev_color node
        if (other.prev_color != nullptr) {
            prev_color = new shape_node(*other.prev_color);
        }
        else {
            prev_color = nullptr;
        }
    }
    return *this;
}
