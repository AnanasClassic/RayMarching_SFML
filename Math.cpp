#include "Math.h"

sf::Vector3f Math::polar(sf::Vector3f cPoint) {
    auto &p = cPoint;
    return sf::Vector3f(
            len(cPoint),
            std::acos(p.x / std::sqrt(p.x * p.x + p.y * p.y)) * (p.y >= 0 ? 1.f : -1.f),
            std::acos(p.z / len(cPoint))
    );
}

sf::Vector3f Math::cartesian(sf::Vector3f pPoint) {
    auto &p = pPoint;
    return sf::Vector3f(
            p.x * std::cos(p.y) * std::sin(p.z),
            p.x * std::sin(p.y) * std::sin(p.z),
            p.x * std::cos(p.z)
    );
}

float Math::scalarProduct(sf::Vector3f v1, sf::Vector3f v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

sf::Vector3f Math::crossProduct(sf::Vector3f v1, sf::Vector3f v2) {
    return sf::Vector3f(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
    );
}

Matrix3f Math::makeSpecificBasis(sf::Vector3f v1) {
    auto e1 = Math::normalise(v1);
    if (e1.x * e1.x + e1.y * e1.y < 0.0001f) {
        e1 += sf::Vector3f{1e-5, 0, 0};
    }
    auto e2 = Math::normalise(crossProduct({0, 0, 1}, e1));
    auto e3 = crossProduct(e1, e2);
    return {e1, e2, e3};
}

Matrix3f Math::T(Matrix3f m) {
    return {{m.x.x, m.y.x, m.z.x},
            {m.x.y, m.y.y, m.z.y},
            {m.x.z, m.y.z, m.z.z}};
}

Matrix3f Math::multiply(Matrix3f m1, Matrix3f m2) {
    auto m2t = T(m2);
    return {
            {
                    scalarProduct(m1.x, m2t.x),
                    scalarProduct(m1.x, m2t.y),
                    scalarProduct(m1.x, m2t.z)
            },
            {
                    scalarProduct(m1.y, m2t.x),
                    scalarProduct(m1.y, m2t.y),
                    scalarProduct(m1.y, m2t.z)
            },
            {
                    scalarProduct(m1.z, m2t.x),
                    scalarProduct(m1.z, m2t.y),
                    scalarProduct(m1.z, m2t.z)
            }
    };
}

sf::Vector3f Math::multiply(Matrix3f m, sf::Vector3f v) {
    return {
            scalarProduct(m.x, v),
            scalarProduct(m.y, v),
            scalarProduct(m.z, v)
    };
}

sf::Vector3f Math::makeNewPoint(sf::Vector3f pPoint, float dphi, float dtheta, const Matrix3f& basis) {
    sf::Vector3f polarp{len(pPoint), dphi, Math::dtor(90) + dtheta};
    sf::Vector3f p = cartesian(polarp);
    auto pp = multiply(T(basis), p);
    return pp;
}