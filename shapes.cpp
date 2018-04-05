//
// Created by Thomas Stockham on 4/5/18.
//

#include "shapes.h"
#include "graphics.h"
#include "math.h"


/******************** point struct ********************/

point::point() : x(0), y(0) { }

point::point(int xIn, int yIn) : x(xIn), y(yIn) { }

/******************** Shape class ********************/

Shape::Shape() : area(0), perimeter(0),
                 center({0, 0}), fill({0, 0, 0}) {
    // color defaults to black
}

Shape::Shape(point c, color f) : area(0), perimeter(0),
                                 center(c), fill(f) { }

Shape::Shape(int xIn, int yIn, double r, double g, double b) :
        area(0), perimeter(0), center({xIn, yIn}), fill({r, g, b}) { }

point Shape::getCenter() const {
    return center;
}

double Shape::getArea() const {
    return area;
}

double Shape::getPerimeter() const {
    return perimeter;
}

color Shape::getFill() const {
    return fill;
}

void Shape::setPoint(point c) {
    center = c;
}

void Shape::setPoint(int xIn, int yIn) {
    center = {xIn, yIn};
}

void Shape::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Shape::setColor(color f) {
    fill = f;
}

void Shape::setColor(double r, double g, double b) {
    fill = {r, g, b};
}

/******************** Circle class ********************/

void Circle::calculateArea() {
    // A = pi*r^2
    area = PI * radius * radius;
}

void Circle::calculatePerimeter() {
    // Circumference = 2*pi*r
    perimeter = 2.0 * PI * radius;
}

Circle::Circle() : Shape(), radius(0) { }

Circle::Circle(double rad) : Shape() {
    // radius not in initializer list because
    // we want to check for value >= 0
    setRadius(rad);
}

Circle::Circle(double rad, point c) : Shape(c, {0, 0, 0}) {
    setRadius(0);
}

Circle::Circle(double rad, int xIn, int yIn) :
        Shape(xIn, yIn, 0, 0, 0) {
    setRadius(rad);
}

Circle::Circle(point c) : Shape(c, {0, 0, 0}), radius(0) { }

Circle::Circle(int xIn, int yIn) : Shape(xIn, yIn, 0, 0, 0),
                                   radius(0) { }

Circle::Circle(color f) : Shape({0, 0}, f), radius(0) { }

Circle::Circle(double r, double g, double b) :
        Shape({0, 0}, {r, g, b}), radius(0) { }

Circle::Circle(double rad, point c, color f) : Shape(c, f) {
    setRadius(rad);
}

Circle::Circle(double rad,
               int xIn, int yIn,
               double r, double g, double b) :
        Shape(xIn, yIn, r, g, b) {
    setRadius(rad);
}

double Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(double rad) {
    // radius should not be negative
    radius = (rad < 0) ? 0 : rad;
    // now recalculate area and perimeter
    calculateArea();
    calculatePerimeter();
}

void Circle::draw() const {
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(center.x, center.y);
    //glColor3f(1.0,1.0,1.0);
    for(double i =0;i<=2.0*PI+0.05;i+=(2.0*PI/360.0)){
        glVertex2i(center.x+(radius*cos(i)), center.y+(radius*sin(i)));
    }
    glEnd();
}

/******************** Rect class ********************/

void Rect::calculateArea() {
    area = length * height;
}

void Rect::calculatePerimeter() {
    perimeter = 2.0 * length + 2.0 * height;
}

Rect::Rect() : Shape(), length(0), height(0) { }

Rect::Rect(double l, double h) : Shape() {
    setDimensions(l, h);
}

double Rect::getWidth() const {
    return length;
}

double Rect::getHeight() const {
    return height;
}

void Rect::setDimensions(double l, double h) {
    // we do not want to accept negative values
    // for length and width
    length = (l < 0) ? 0 : l;
    height = (h < 0) ? 0 : h;
    // now update area and perimeter
    calculateArea();
    calculatePerimeter();
}

void Rect::draw() const {
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    //top left
    glVertex2i(center.x-(length/2.0),center.y-(height/2.0));
    //top right
    glVertex2i(center.x+(length/2.0),center.y-(height/2.0));
    //bottom right
    glVertex2i(center.x+(length/2.0),center.y+(height/2.0));
    //bottom left
    glVertex2i(center.x-(length/2.0),center.y+(height/2.0));
    glEnd();
}


