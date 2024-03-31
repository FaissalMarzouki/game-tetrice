#include "piece.h"
#include "raylib.h"
float piece::spaceLeft = 0.0f;
float piece::spaceRight = 80.0f;
piece::piece() {
    _color = color_ni;
    _shape = shape_ni;
    x = 0.0f;
    y = 0.0f;
}

piece::piece(shape s, shape_color c, float x, float y) {
    _shape = s;
    _color = c;
    this->x = x;
    this->y = y;
}

piece::piece(int shapes_count, int colors_count) {
    int s = (rand() % shapes_count) + 1;
    int c = (rand() % colors_count) + 1;

    _shape = static_cast<shape>(s);
    _color = static_cast<shape_color>(c);
    this->x = 100.0f;
    this->y = 100.0f;

}
piece::piece(const piece& other) {
    _shape = other._shape;
    _color = other._color;
    x = other.x;
    y = other.y;
}

void piece::set_shape(shape s) {
    _shape = s;
}

void piece::set_color(shape_color c) {
    _color = c;
}

void piece::set_X(float x) {
    this->x = static_cast<float>(x);
}

void piece::set_Y(float y) {
    this->y = static_cast<float>(y);
}
float piece::get_X() const {
    return x;
}

float piece::get_Y() const {
    return y;
}

shape piece::get_shape() const {
    return _shape;
}

shape_color piece::get_color() const {
    return _color;
}

piece::~piece() {
}

piece& piece::operator=(const piece& other) {
    if (this != &other) {
        _shape = other._shape;
        _color = other._color;
        x = other.x;
        y = other.y;
    }
    return *this;
}

void piece::afficher() const{
    switch (_color) {
    case Red:
        cout << "\033[31m"; 
        break;
    case Green:
        cout << "\033[32m"; 
        break;
    case Yellow:
        cout << "\033[33m"; 
        break;
    case Blue:
        cout << "\033[34m";
        break;
    default:
        break;
    }
    switch (_shape) {
    case Cercle:
        cout << "C";
        break;
    case Rhombus:
        cout << "R";
        break;
    case Square:
        cout << "S";
        break;
    case Triangle:
        cout << "T";
        break;
    default:
        break;
    }
    cout << "\033[0m  ";
}

void piece::draw() {
    Color raylibColor;
    switch (_color) {
    case Red:
        raylibColor = RED;
        break;
    case Green:
        raylibColor = GREEN;
        break;
    case Yellow:
        raylibColor = YELLOW;
        break;
    case Blue:
        raylibColor = BLUE;
        break;
    default:
        raylibColor = WHITE;
        break;
    }

    switch (_shape) {
    case Cercle:
        DrawCircle(static_cast<float>(this->x), static_cast<float>(this->y), 20.0f, raylibColor);
        break;
    case Rhombus:
        DrawRectanglePro(Rectangle{ static_cast<float>(this->x), static_cast<float>(this->y), 40.0f, 40.0f }, { 20.0f, 20.0f }, 45.0f, raylibColor);
        break;
    case Square:
        DrawRectangleRec(Rectangle{ static_cast<float>(this->x), static_cast<float>(this->y), 40.0f, 40.0f }, raylibColor);
        break;
    case Triangle:
        DrawTriangle({ static_cast<float>(this->x), static_cast<float>(this->y) }, { static_cast<float>(this->x) + 40.0f, static_cast<float>(this->y) }, { static_cast<float>(this->x) + 20.0f, static_cast<float>(this->y) - 35.0f }, raylibColor);
        break;
    default:
        break;
    }
}

