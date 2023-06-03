#pragma once
#include "SFML/Graphics.hpp"

class Shape {
public:
    virtual  float len(sf::Vector3f p) = 0;
};

class Sphere : public Shape {
    sf::Vector3f pos;
    float radius;
public:
    float len(sf::Vector3f p) override {
        return Math::len(p - pos) - radius;
    }
    Sphere(sf::Vector3f pos, float radius) : pos(pos), radius(radius) {}
};

class Floor : public Shape {
    float height;
public:
    float len(sf::Vector3f p) override {
        return p.z - height;
    }
    Floor(float height) : height(height) {}
};

