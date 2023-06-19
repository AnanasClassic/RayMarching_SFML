#pragma once

#include "SFML/Graphics.hpp"
#include "Ray.h"
#include "Shape.h"
#include "RMalgo.h"
#include "Math.h"

template<size_t width, size_t height>
class Camera {

    const sf::Color lightColor = sf::Color(255, 255, 255);
    const sf::Color fogColor = sf::Color(63, 63, 255);

    sf::Vector3f pos;
    sf::Vector2f dir;
    sf::Image screen;
    std::vector<std::vector<Ray>> rays;
    sf::Vector2f fov = sf::Vector2f(90, 90);
public:

    Camera() : pos(sf::Vector3f(0, 0, 0)), dir(sf::Vector2f(0, 0)),
               rays(height, std::vector<Ray>(width)) {
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
                auto dtheta = Math::dtor(fov.y * (i - height / 2) / height);
                auto dphi = Math::dtor(fov.x * (j - width / 2) / height);
                rays[i][j] = Ray(pos, Math::makeNewPoint(cDir, dphi, dtheta, basis));
                auto pray = Math::polar(rays[i][j].getDir());
                pray = -pray;

            }
        }
    }

    static sf::Color mult(const sf::Color &color, float alpha) {
        return sf::Color(color.r * alpha, color.g * alpha, color.b * alpha);
    }

    void frame(const std::vector<Shape *> &objects) {
        createRays();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                Ray &ray = rays[i][j];
                sf::Color color;
                if (RMalgo::RayMarch(ray, objects)) {
                    sf::Vector3f grad = Math::normalise(RMalgo::getGradient(ray, objects));
                    auto skyCos = Math::scalarProduct({0, 0, 1}, grad) / 2 + 0.5;
                    auto rayCos = std::abs(Math::scalarProduct(Math::normalise(ray.getDir()), grad));
                    auto rayLen = Math::len(pos - ray.getPos()) / RMalgo::max_dist_limit;
                    float raySkyRatio = 0.2f;
                    auto lightness = (rayCos * raySkyRatio + skyCos * (1 - raySkyRatio));
                    auto fogCoefficient = 1 - std::pow(std::max(1.f - rayLen, 0.f), 2);
                    color = mult(mult(lightColor, lightness), 1 - fogCoefficient) + mult(fogColor, fogCoefficient);
                } else {
                    color = fogColor;
                }
                screen.setPixel(j, i, color);
            }
        }
    }
};