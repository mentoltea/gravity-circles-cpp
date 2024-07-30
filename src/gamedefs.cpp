#include "gamedefs.h"

Vec2 Vec2::operator+(const Vec2 &v) const {
    return {this->x + v.x, this->y + v.y};
}
Vec2& Vec2::operator+=(const Vec2 &v) {
    x += v.x;
    y += v.y;
    return *this;
}
Vec2 Vec2::operator-() const {
    return {-x, -y};
}
Vec2 Vec2::operator-(const Vec2 &v) const {
    return {this->x - v.x, this->y - v.y};
}
Vec2& Vec2::operator-=(const Vec2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

float Vec2::operator*(const Vec2 &v) const {
    return x*v.x + y*v.y;
}
Vec2 Vec2::operator*(float k) const {
    return {k*x, k*y};
}
Vec2& Vec2::operator*=(float k) {
    x *= k;
    y *= k;
    return *this;
}

float Vec2::length() const {
    return sqrt(x*x + y*y);
}
Vec2 Vec2::normalize() const {
    float l = length();
    return {x/l, y/l};
}

bool Vec2::operator==(const Vec2 &v) const {
    return (x==v.x)&&(y==v.y);
}

float Vec2::dist(const Vec2 &v) const {
    return sqrt( (x-v.x)*(x-v.x) + (y-v.y)*(y-v.y) );
}

Vec2::operator Point() const {
    return Point(x, y);
}

Vec2 operator*(float k, const Vec2 &v) {
    return {k*v.x, k*v.y};
}

Circle::Circle(Vec2 pos, Vec2 vel, float rad, float mass, Color color): pos(pos), vel(vel), rad(rad), mass(mass), color(color) {
    ObjectsToDraw.push_back(this);
    circles.push_back(this);
}
Circle::~Circle() {
    RemoveFromVector(this);
    Remove();
}

void Circle::Remove() {
    for (auto it = circles.begin(); it != circles.end(); it++) {
        if (*it == this) {
            circles.erase(it);
            break;
        }
    }
}

Vec2 Circle::Acceleration() {
    Vec2 f = {0,0};
    Vec2 temp;
    float d;
    for (auto it = circles.begin(); it != circles.end(); it++) {
        if (*it == this) continue;
        d = pos.dist((*it)->pos);
        if (d==0) d = 0.01;
        temp = ((*it)->pos - pos).normalize();
        f += temp * (G * (*it)->mass/ d / d);
    }
    accel = f;
    return f;
}

void Circle::tick() {
    if (pos.x >= WINX) {
        pos.x -= WINX;
    } else if (pos.x < 0) {
        pos.x += WINX;
    }
    if (pos.y >= WINY) {
        pos.y -= WINY;
    } else if (pos.y < 0) {
        pos.y += WINY;
    }
    
    vel *= vKoef;
    vel += Acceleration();

    float mult;
    float m1, m2;
    float l1, l2;
    Vec2 v1, v2;
    for (auto it = circles.begin(); it != circles.end(); it++) {
        if (*it == this) continue;
        if (pos.dist((*it)->pos) <= rad+(*it)->rad
            && collisions[*it]!=curtick) {
            v1 = vel;
            v2 = (*it)->vel;
            mult = v1*v2;
            if (mult==0) {
                vel = -v1;
                (*it)->vel = -v2;
            }
            else if (0) {
                l1 = v1.x*v1.x + v1.y*v1.y;
                l2 = v2.x*v2.x + v2.y*v2.y;
                m1 = mass;
                m2 = (*it)->mass;

                vel = mult/l2*v2 + (1 - m2/m1*mult/l1)*v1;
                (*it)->vel = mult/l1*v1 + (1 - m1/m2*mult/l2)*v2;
            } else {
                l1 = 1 - v2.length()/v1.length();
                l2 = 1 - v1.length()/v2.length();

                vel = v2 + l1*v1;
                (*it)->vel = v1 + l2*v2;
            }
            collisions[*it] = curtick;
            (*it)->collisions[this] = curtick;
        }
    }
    pos += vel;
}



void Circle::draw() {
    draw_filled_circle(pos, rad, color);
    draw_line(pos, pos+40*vel, {0,0,255});
    draw_line(pos, pos+mass*200*accel, {255,0,0});
}