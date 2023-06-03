#pragma once
#include "SFML/Graphics.hpp"

class Ray {
    sf::Vector3f pos{0,0,0};
    sf::Vector3f dir{1,0,0};
public:
    Ray() = default;
    Ray(sf::Vector3f pos, sf::Vector3f dir) : pos(pos), dir(dir) {}
    sf::Vector3f getPos() { return pos; }
    sf::Vector3f getDir() { return dir; }
    virtual void Step(float dt) { pos += dir * dt; }
};