#pragma once

#include "SFML/Graphics.hpp"
#include "Ray.h"
#include "Shape.h"
#include "Math.h"

struct RMalgo {
    static const float max_dist_limit;
    static const float min_dist_limit;
    static const float precision;

    static float getDist(sf::Vector3f point, const std::vector<Shape *> &objects) {
        float min_dist = max_dist_limit;
        for (auto &object: objects) {
            min_dist = std::min(min_dist, object->dist(point));
        }
        return min_dist;
    }

    static bool RayMarch(Ray& ray, const std::vector<Shape *> &objects) {
        auto begin = ray.getPos();
        float min_dist = max_dist_limit;
        while (min_dist > min_dist_limit) {
            min_dist = getDist(ray.getPos(), objects);
            if (max_dist_limit - min_dist < precision || Math::len(ray.getPos() - begin) > max_dist_limit) {
                return false;
            } else if (min_dist < min_dist_limit) {
                return true;
            }
            ray.Step(min_dist);
        }
    }

    static sf::Vector3f getGradient(Ray &ray, const std::vector<Shape *> &objects) {
        auto basis = Math::makeSpecificBasis(ray.getDir());
        return {
//                (getDist(ray.getPos() + basis.x * precision, objects) -
//                 getDist(ray.getPos() - basis.x * precision, objects)) / precision,
//                (getDist(ray.getPos() + basis.y * precision, objects) -
//                 getDist(ray.getPos() - basis.y * precision, objects)) / precision,
//                (getDist(ray.getPos() + basis.z * precision, objects) -
//                 getDist(ray.getPos() - basis.z * precision, objects)) / precision
                (getDist(ray.getPos() + sf::Vector3f(1, 0, 0) * precision, objects) -
                 getDist(ray.getPos() - sf::Vector3f(1, 0, 0) * precision, objects)) / precision,
                (getDist(ray.getPos() + sf::Vector3f(0, 1, 0) * precision, objects) -
                 getDist(ray.getPos() - sf::Vector3f(0, 1, 0) * precision, objects)) / precision,
                (getDist(ray.getPos() + sf::Vector3f(0, 0, 1) * precision, objects) -
                 getDist(ray.getPos() - sf::Vector3f(0, 0, 1) * precision, objects)) / precision
        };
    }
};

const float RMalgo::precision = 0.00002f;
const float RMalgo::max_dist_limit = 80.f;
const float RMalgo::min_dist_limit = 0.00001f;