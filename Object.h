#pragma once
#include "SFML/Graphics.hpp"

class Object {
public:
    virtual  float len(sf::Vector3f p) = 0;
};

class Sphere : public Object {
    sf::Vector3f pos;
    float radius;
public:
    float len(sf::Vector3f p) override {
        return Math::len(p - pos) - radius;
    }
    Sphere(sf::Vector3f pos, float radius) : pos(pos), radius(radius) {}
};

