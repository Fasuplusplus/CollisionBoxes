//Dos cajas una pared y suelo sin fricción https://www.youtube.com/watch?v=HEfHFsfGXjs contar número de colisiones
//La pared está en X=0
#include <cmath>
#include <iostream>
#include <string>
#include <windows.h>
double step = 0.0001;
class body {
public:
    double mass = 1;
    double Xpos = 1000000000;
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
                    printf("boing\n");
                    printf("%i\n", i);
                    box[i].XellasticCollision(box[e].mass, box[e].Xvel);
                }
            }
        }
    }
    for (int i = 0; i < boxcount; i++) {
        box[i].Xvel = box[i].newXvel;
    }
}

void allMovements() {
    for (int i = 0; i < boxcount; i++) {
        box[i].move();
        std::cout << "box " << i << " Xpos: " << box[i].Xpos << "  Xvel: " << box[i].Xvel << "\n";
    }
}

int main() {
    placebody(box[0], 4, 2, 5, 1, true);
    placebody(box[1], 9, 2, -5, 1, true);
    bool stop = false;
    while (stop == false) {
        allCollisions();
        allMovements();
        if (GetAsyncKeyState(VK_ESCAPE /*funciona no le hagas caso a las lineas rojas*/)) {
            printf("exited\n");
            stop = true;
        }
    }
    return 0;
}
