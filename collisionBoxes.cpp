//Dos cajas una pared y suelo sin fricción https://www.youtube.com/watch?v=HEfHFsfGXjs contar número de colisiones
//La pared está en X=0
#include <cmath>
#include <iostream>
#include <string>
double step = 0.0001;
class body {
public:
    double mass = 1;
    double Xpos = 1000000000;
    double Xspeed = 0;
    double radius = 0;
    void move() {
        Xpos = Xpos + (Xspeed * step);
    }
    bool checkCollision(double otherPos, double otherRadius) {
       if ((fabs(Xpos - otherPos)) <= (radius + otherRadius)) {
            return true;
        }
        else {
            return false;
        }
    }
};

body wall;
int boxcount = 0;
body box[999];
void placebody(body &i, double Xpos, double radius, double Xspeed, double mass, bool isbox) {
    i.Xpos = Xpos;
    i.radius = radius;
    i.Xspeed = Xspeed;
    i.mass = mass;
    if (isbox == true) {
        boxcount++;
    }
}

int main() {
    placebody(box[0], 3.348, 2, 5, 1, true);
    placebody(box[1], 10.007, 2, -5, 1, true);
    bool collision = false;
    while (collision == false) {
        for (int i = 0; i < boxcount; i++) {
            for (int e = 0; e < boxcount; e++) {
                if (e != i) {
                    if (box[i].checkCollision(box[e].Xpos, box[e].radius)) {
                        printf("boom");
                        collision = true;
                        break;
                    }
                }
            }
            if (collision == true) {
                break;
            }
        }
        if (collision == true) {
            break;
        }
        for (int i = 0; i < boxcount; i++) {
            box[i].move();
            std::cout << "box " << i << " Xpos: " << box[i].Xpos << "  Xspeed: " << box[i].Xspeed << "\n";
        }
    }
    return 0;
}
