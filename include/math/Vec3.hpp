// Vec3.hpp - Minimal mathematicals types of the simulation.
#pragma once

#include <algorithm>
#include <cmath>

namespace mecha {

constexpr float kPi = 3.14158265358979323846f;
constexpr float kTwoPi = 2.0f * kPi;

struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    constexpr Vec3() = default;
    constexpr Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    // Axis index access: 0 = X, 1 = Y, 2 = z. Allow to solve axis collisions.
    float& operator[](int axis) { return axis == 0 ? x : (axis == 1 ? y : z); }
    const float& operator[](int axis) const { return axis == 0 ? x : (axis == 1 ? y : z); }
}
} // namespace mecha
