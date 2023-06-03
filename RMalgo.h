#pragma once

#include "SFML/Graphics.hpp"
#include "Ray.h"
#include "Object.h"
#include "Math.h"

struct RMalgo {
    static const float max_dist_limit;
    static const float min_dist_limit;
    static const float precision;

    static float getDist(sf::Vector3f point, const std::vector<Object *> &objects) {
        float min_dist = max_dist_limit;
        for (auto &object: objects) {
            min_dist = std::min(min_dist, object->len(point));
        }
        return min_dist;
    }

    static bool RayMarch(Ray &ray, const std::vector<Object *> &objects) {
        float min_dist = max_dist_limit;
        while (min_dist > min_dist_limit) {
            min_dist = getDist(ray.getPos(), objects);
            if (max_dist_limit - min_dist < precision) {
                return false;
            } else if (min_dist < min_dist_limit) {
                return true;
            }
            ray.Step(min_dist);
        }
        return true;
    }

    static sf::Vector3f getGradient(Ray &ray, const std::vector<Object *> &objects) {
        auto basis = Math::makeSpecificBasis(ray.getDir());
        return {
                (getDist(ray.getPos() + basis.x * precision, objects) -
                 getDist(ray.getPos() - basis.x * precision, objects)) / precision,
                (getDist(ray.getPos() + basis.y * precision, objects) -
                 getDist(ray.getPos() - basis.y * precision, objects)) / precision,
                (getDist(ray.getPos() + basis.z * precision, objects) -
                 getDist(ray.getPos() - basis.z * precision, objects)) / precision
        };
    }
};

const float RMalgo::precision = 0.001f;
const float RMalgo::max_dist_limit = 100.f;
const float RMalgo::min_dist_limit = 0.001f;