//Dos cajas una pared y suelo sin fricción https://www.youtube.com/watch?v=HEfHFsfGXjs contar número de colisiones
//La pared está en X=0
#include <cmath>
#include <iostream>
#include <string>
#include <windows.h>
double decimals = 10; //para calcular pi
double step = 2/(3.2*pow(10, decimals)*5);
int collisions = 0;
class body {
public:
    double mass = 1;
    double Xpos = 10000000000;
    double Xvel = 0;
    double newXvel = 0;
    double radius = 0;
    void move() {
        Xpos = Xpos + (Xvel * step);
    }
    bool checkCollision(double otherPos, double otherRadius) {
        if ((fabs(Xpos - otherPos)) <= (radius + otherRadius)) {
            return true;
        }
        else {
            return false;
        }
    }
    void XellasticCollision(double otherMass, double otherXvel) {
        newXvel = (((Xvel * (mass - otherMass)) + (2 * otherMass * otherXvel)) / (mass + otherMass));
    }
    void XwallCollision() {
        newXvel = -1 * Xvel;
    }
};

body wall;
int boxcount = 0;
body box[999];
void placebody(body &i, double Xpos, double radius, double Xvel, double mass, bool isbox) {
    i.Xpos = Xpos;
    i.radius = radius;
    i.Xvel = Xvel;
    i.mass = mass;
    if (isbox == true) {
        boxcount++;
    }
}

void allCollisions() {
    for (int i = 0; i < boxcount; i++) {
        box[i].newXvel = box[i].Xvel;
        for (int e = 0; e < boxcount; e++) {
            if (e != i) {
                if (box[i].checkCollision(box[e].Xpos, box[e].radius) || box[i].checkCollision(wall.Xpos, wall.radius)) {
                    collisions++;
                    box[i].XellasticCollision(box[e].mass, box[e].Xvel);
                }
            }
        }
        if (box[i].checkCollision(wall.Xpos, wall.radius)) {
            box[i].XwallCollision();
            collisions++;
        }
    }
    for (int i = 0; i < boxcount; i++) {
        box[i].Xvel = box[i].newXvel;
    }
}

void allMovements() {
    for (int i = 0; i < boxcount; i++) {
        box[i].move();
    }
}

int main() {
    placebody(wall, -2, 2, 0, 0, false);
    placebody(box[0], 2.2, 2, 0, 1, true);
    placebody(box[1], 6.4, 2, -5, pow(100, decimals), true);
    bool stop = false;
    int check = 0;
    while (stop == false) {
        allCollisions();
        allMovements();
        if (GetAsyncKeyState(VK_ESCAPE)) {
            printf("exited\n");
            stop = true;
        }
        if ((box[0].Xvel >= 0) && (box[1].Xvel >= 0) && (box[0].Xvel < box[1].Xvel)) {
            break;
        }
        check++;
        if (check == 100000000) {
            for (int i = 0; i < boxcount; i++) {
                std::cout << "box " << i << " Xpos: " << box[i].Xpos << "  Xvel: " << box[i].Xvel << "\n";
            }
            std::cout << "pi: " << (collisions/2) << "\n";
            check = 0;
        }
    }
    std::cout << "pi = " << (collisions / 2) << "\n";
    return 0;
}
