// Vec3.hpp - Minimal mathematical types for the simulation.
#pragma once

#include <cmath>
#include <stdexcept>

namespace mecha {

constexpr float kPi = 3.14159265358979323846f;
constexpr float kTwoPi = 2.0f * kPi;

// Three-dimensional vector with float components.
struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    constexpr Vec3() = default;
    constexpr Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    // Axis access: 0 = X, 1 = Y, and 2 = Z.
    constexpr float& operator[](int axis) {
        if (axis == 0)
            return x;
        if (axis == 1)
            return y;
        if (axis == 2)
            return z;
        throw std::out_of_range("Vec3 axis index must be 0, 1, or 2");
    }

    constexpr const float& operator[](int axis) const {
        if (axis == 0)
            return x;
        if (axis == 1)
            return y;
        if (axis == 2)
            return z;
        throw std::out_of_range("Vec3 axis index must be 0, 1, or 2");
    }

    constexpr Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    constexpr Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    constexpr Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }
    constexpr Vec3 operator/(float s) const { return {x / s, y / s, z / s}; }
    constexpr Vec3 operator-() const { return {-x, -y, -z}; }
    Vec3& operator+=(const Vec3& o) {
        x += o.x;
        y += o.y;
        z += o.z;
        return *this;
    }
    Vec3& operator-=(const Vec3& o) {
        x -= o.x;
        y -= o.y;
        z -= o.z;
        return *this;
    }
    Vec3& operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
};

constexpr Vec3 operator*(float s, const Vec3& v) { return v * s; }

constexpr float Dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
constexpr Vec3 Cross(const Vec3& a, const Vec3& b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
constexpr float LengthSq(const Vec3& v) { return Dot(v, v); }
inline float Length(const Vec3& v) { return std::sqrt(LengthSq(v)); }

// Returns a unit vector, or `fallback` when the input is too close to zero.
inline Vec3 Normalized(const Vec3& v, const Vec3& fallback = Vec3{}) {
    const float lenSq = LengthSq(v);
    if (lenSq < 1e-12f)
        return fallback;
    return v * (1.0f / std::sqrt(lenSq));
}

constexpr float Clamp(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }
constexpr float Lerp(float a, float b, float t) { return a + (b - a) * t; }
constexpr Vec3 Lerp(const Vec3& a, const Vec3& b, float t) { return a + (b - a) * t; }

// Moves `current` toward `target` by at most `maxDelta` (which must be non-negative).
inline float MoveTowards(float current, float target, float maxDelta) {
    if (maxDelta < 0.0f)
        throw std::invalid_argument("MoveTowards maxDelta must be non-negative");

    const float diff = target - current;
    if (std::fabs(diff) <= maxDelta)
        return target;
    return current + (diff > 0.0f ? maxDelta : -maxDelta);
}

// Wraps an angle in radians to the range [-pi, pi).
inline float WrapAngle(float radians) {
    float a = std::fmod(radians + kPi, kTwoPi);
    if (a < 0.0f)
        a += kTwoPi;
    return a - kPi;
}

// Interpolates between two angles along the shortest path.
inline float AngleLerp(float from, float to, float t) { return from + WrapAngle(to - from) * t; }

} // namespace mecha
