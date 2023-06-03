#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

using Matrix3f = sf::Vector3<sf::Vector3f>;
struct Math {
    class Angle {
        explicit operator float() const { return radians; }
        explicit operator float&() { return radians; }
        Angle(float radians_) : radians(normalize(radians_)) {}
        Angle(const Angle& other) : radians(other.radians) {}
        Angle& operator=(float radians_) { radians = normalize(radians_); return *this; }
        Angle& operator=(const Angle& other) = default;
        Angle& operator+=(const Angle& other);
        Angle& operator-=(const Angle& other);
        Angle operator+(const Angle& other) const;
        Angle operator-(const Angle& other) const;
    private:
        float radians;
        static float normalize(float t);
    };
    static float len(sf::Vector3f v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
    static sf::Vector3f normalise(sf::Vector3f v) { return v / len(v); }
    static float rtod(float radians) { return radians * 180.f / static_cast<float>(M_PI); }
    static float dtor(float degrees) { return degrees * static_cast<float>(M_PI) / 180.f; }
    static sf::Vector3f polar(sf::Vector3f cPoint);
    static sf::Vector3f cartesian(sf::Vector3f pPoint);
    static float scalarProduct(sf::Vector3f v1, sf::Vector3f v2);
    static sf::Vector3f crossProduct(sf::Vector3f v1, sf::Vector3f v2);
    static sf::Vector3<sf::Vector3f> makeSpecificBasis(sf::Vector3f v1);
    static sf::Vector3f makeNewPoint(sf::Vector3f pPoint, float dphi, float dtheta, const Matrix3f& basis);
    static Matrix3f T(Matrix3f m);
    static Matrix3f multiply(Matrix3f m1, Matrix3f m2);
    static sf::Vector3f multiply(Matrix3f m, sf::Vector3f v);
};