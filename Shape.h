#pragma once
#include "SFML/Graphics.hpp"

class Shape {
public:
    virtual  float dist(sf::Vector3f p) = 0;
    virtual ~Shape() = default;
};

class Sphere : public Shape {
    sf::Vector3f pos;
public:
    float dist(sf::Vector3f p) override {
        return Math::len(p - pos) - radius;
    }
    float radius;
    Sphere(sf::Vector3f pos, float radius) : pos(pos), radius(radius) {}
};

class Floor : public Shape {
    float height;
public:
    float dist(sf::Vector3f p) override {
        return p.z - height;
    }
    Floor(float height) : height(height) {}
};

class Box : public Shape {
    sf::Vector3f pos;
public:
    float dist(sf::Vector3f p) override {
        return std::max({std::abs(p.x - pos.x) - size.x, std::abs(p.y - pos.y) - size.y, std::abs(p.z - pos.z) - size.z});
    }
    Box(sf::Vector3f pos, sf::Vector3f size) : pos(pos), size(size/2.f) {}

    sf::Vector3f size;
};

class Cube : public Box {
public:
    Cube(sf::Vector3f pos, float size) : Box(pos, {size, size, size}) {}
    friend class CubeWithoutSphere;
};

class CubeWithoutSphere : public Shape {
    Sphere sphere;
    Cube cube;
public:
    CubeWithoutSphere(sf::Vector3f pos, float size, float ratio) : sphere(pos, size * ratio), cube(pos, size) {}
    float dist(sf::Vector3f p) override {
//        if (cube.dist(p) > 0) {
//            return cube.dist(p);
//        } else {
//            auto dst = sphere.dist(p);
//            return dst;
//        }
        return std::max(cube.dist(p), -sphere.dist(p));
    };
};

class CubeWithoutSphereCicled : public CubeWithoutSphere {
public:
    float size;
    sf::Vector3f pos;
    CubeWithoutSphereCicled(sf::Vector3f pos, float size, float ratio) : CubeWithoutSphere(pos, size, ratio), size(size), pos(pos) {}
    float dist(sf::Vector3f p) override {
        return CubeWithoutSphere::dist({Math::cycle(p.x, pos.x - size / 2, pos.x + size / 2), Math::cycle(p.y, pos.y - size / 2, pos.y + size / 2), Math::cycle(p.z, pos.z - size / 2, pos.z + size / 2)});
    }
};


class RandomSphere : public Shape {
    sf::Vector3f center;
    float radius;
public:
    float dist(sf::Vector3f p) override {
        if (Math::len(p - center) < radius) {
            return ((std::rand() % 14) - 1) / 100.f;
        }
        return Math::len(p - center);
    }
    RandomSphere(sf::Vector3f center, float radius) : center(center), radius(radius) {}
};

class BasicMandelbrot : public Floor {
  static const int max_iter = 64;
  static void iter(sf::Vector2f& p, sf::Vector2f c) {
    p = {c.x + p.x * p.x - p.y * p.y, c.y + 2 * p.x * p.y};
  }
  static float calculate(sf::Vector2f point) {
    sf::Vector2f c;
    for (int i = 1; i < max_iter; ++i) {
      iter(c, point);
      if (c.x * c.x + c.y * c.y > 4) {
        return i;
      }
    }
    return max_iter;
  };
 public:
  BasicMandelbrot(float height) : Floor(height) {}
  float dist(sf::Vector3f p) override {
    auto d = Floor::dist(p);
    if (d > 1) {
      return d;
    }
    auto calc = calculate({p.x, p.y});
    return d - 1 / calc;
  }
};

class Thorus : public Shape {
 protected:
  sf::Vector3f center;
  float radius;
  float thickness;
 public:
  Thorus(sf::Vector3f center, float radius, float thickness) : center(center), radius(radius), thickness(thickness) {}
  float dist(sf::Vector3f p) override {
      float dx = p.x - center.x;
      float dy = p.y - center.y;
      float dz = p.z - center.z;
      float circleLen = std::sqrt(dx * dx + dy * dy) - radius;
      return std::sqrt(circleLen * circleLen + dz * dz) - thickness;
  }
};

class CycledThorus : public Thorus {
 public:
  CycledThorus(sf::Vector3f center, float radius, float thickness) : Thorus(center, radius, thickness) {}
  float dist(sf::Vector3f p) override {
    return Thorus::dist({Math::cycle(p.x, Thorus::center.x - Thorus::radius - Thorus::thickness,
                                          Thorus::center.x + Thorus::radius + Thorus::thickness),
                         Math::cycle(p.y, Thorus::center.y - Thorus::radius - Thorus::thickness,
                                          Thorus::center.y + Thorus::radius + Thorus::thickness), p.z});
  }
};