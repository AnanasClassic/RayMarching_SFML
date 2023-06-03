#pragma once

#include "SFML/Graphics.hpp"
#include "Ray.h"
#include "Object.h"
#include "RMalgo.h"
#include "Math.h"

template<size_t width, size_t height>
class Camera {
    sf::Vector3f pos;
    sf::Vector2f dir;
    sf::Image screen;
    std::vector<std::vector<Ray>> rays;
    sf::Vector2f fov = sf::Vector2f(90, 90);
public:

    Camera() : pos(sf::Vector3f(0, 0, 0)), dir(sf::Vector2f(0, 0)),
                                      rays(width, std::vector<Ray>(height)) {
        screen.create(width, height);
    }

    sf::Vector2u getSize() { return sf::Vector2u(width, height); }
    sf::Vector3f getPos() { return pos; }
    sf::Vector2f getDir() { return dir; }
    sf::Vector2f getFov() { return fov; }
    const sf::Image &getScreen() { return screen; }

    void setPos(sf::Vector3f pos) { this->pos = pos; }
    void setDir(sf::Vector2f dir) { this->dir = dir; }
    void setFov(sf::Vector2f fov) { this->fov = fov; }

    void createRays() {
        auto cDir = Math::cartesian({1, dir.x, dir.y});
        Matrix3f basis = Math::makeSpecificBasis(cDir);
        for (float i = 0; i < height; ++i) {
            for (float j = 0; j < width; ++j) {
                auto dtheta = Math::dtor(fov.y * (static_cast<int>(height) / 2 - i) / height);
                auto dphi = Math::dtor(fov.x * (static_cast<int>(width) / 2 - j) / width);
                rays[i][j] = Ray(pos, Math::makeNewPoint(cDir, dtheta, dphi, basis));
            }
        }
    }

    void frame(const std::vector<Object *> &objects) {
        createRays();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                Ray& ray = rays[i][j];
                sf::Color color;
                if (RMalgo::RayMarch(ray, objects)) {
                    auto grad = RMalgo::getGradient(ray, objects);
                    grad = Math::normalise(grad);
                    grad += {1,1,1};
                    grad /= 2.f;
                    color = sf::Color(grad.x * 255, grad.y * 255, grad.z * 255);
                } else {
                    color = sf::Color(127, 127, 127);
                }
                screen.setPixel(j, i, color);
            }
        }
    }
};