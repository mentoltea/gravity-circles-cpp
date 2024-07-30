#include "gamedefs.h"

size_t WINX=700, WINY=700;

std::vector<Circle*> Circle::circles;
int curtick = 0;

float mass_to_rad(float mass) {
    return 50*mass;
}

void prepare() {
    srand(time(NULL));
    setFPS(30);

    int N = 4;
    int tx, ty, r, g, b;
    float tr, tm;
    for (int i=0; i<N; i++) {
        tx = rand()%WINX;
        ty = rand()%WINY;
        tm = (float)(rand()%201) / 100;
        r = rand()%256; g = rand()%256; b = rand()%256;
        new Circle((Vec2){(float)tx, (float)ty}, (Vec2){0,0}, mass_to_rad(tm), tm, (Color){r, g, b});
    }
}

void call() {
    for (auto it=Circle::circles.begin(); it!=Circle::circles.end(); it++) {
        (*it)->tick();
    }
    curtick++;
    curtick = curtick%(2*iFPS);
}

void end() {
    for (auto it=Circle::circles.begin(); it!=Circle::circles.end(); it++) {
        delete (*it);
    }
}