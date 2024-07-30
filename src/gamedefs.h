#include "definitions.h"
#include <random>
#include <time.h>
#include <map>

#pragma once


const float G = 4;
const float vKoef = 1.f;
extern int curtick;

struct Vec2 {
    float x, y;
    
    Vec2 operator+(const Vec2 &v) const;
    Vec2& operator+=(const Vec2 &v);
    Vec2 operator-() const;
    Vec2 operator-(const Vec2 &v) const;
    Vec2& operator-=(const Vec2 &v);

    float operator*(const Vec2 &v) const;
    Vec2 operator*(float k) const;
    Vec2& operator*=(float k);
    friend Vec2 operator*(float k, const Vec2 &v);


    float length() const;
    Vec2 normalize() const;

    bool operator==(const Vec2 &v) const;

    float dist(const Vec2 &v) const;
    operator Point() const;
};

struct Circle: public DrawableObject {
    Vec2 pos, vel;
    float rad, mass;
    Color color;
    mutable Vec2 accel;

    static std::vector<Circle*> circles;
    std::map<Circle*, int> collisions;

    Circle(Vec2 pos, Vec2 vel, float rad, float mass, Color color);
    ~Circle();

    void Remove();

    Vec2 Acceleration();

    void tick();

    void draw() override;
};