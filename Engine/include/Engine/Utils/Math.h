#pragma once

#include <cmath>
#include <numbers>

constexpr float PI = std::numbers::pi_v<float>;


struct Vector2D {
    float x = 0;
    float y = 0;

    // --- Constructeurs ---
    Vector2D() = default;
    Vector2D(float _x, float _y) : x(_x), y(_y) {}

    // --- Addition ---
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // --- Soustraction ---
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    // --- Multiplication par un Vector2D ---
    Vector2D operator*(const Vector2D& other) const {
        return Vector2D(x * other.x, y * other.y);
    }

    Vector2D& operator*=(const Vector2D& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    // --- Multiplication par un scalaire ---
    Vector2D operator*(float i_scalar) const {
        return Vector2D(x * i_scalar, y * i_scalar);
    }

    Vector2D& operator*=(float i_scalar) {
        x *= i_scalar;
        y *= i_scalar;
        return *this;
    }

    // --- Division par un scalaire (optionnel) ---
    Vector2D operator/(float i_scalar) const {
        return Vector2D(x / i_scalar, y / i_scalar);
    }

    Vector2D& operator/=(float i_scalar) {
        x /= i_scalar;
        y /= i_scalar;
        return *this;
    }
};

struct Vector3D {
    float x = 0;
    float y = 0;
    float z = 0;

    // --- Constructeurs ---
    Vector3D() = default;
    Vector3D(float _x, float _y, float _z) : x(_x), y(_y) , z(_z){}
};



inline float radToDeg(float i_rad) {
    return i_rad * (180.0f / PI);
}

inline float degToRad(float i_deg) {
    return i_deg * (PI / 180.0f);
}