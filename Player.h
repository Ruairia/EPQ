//
// Created by ruairi on 03/08/2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Vector2D.h"

namespace raycaster {

class Player {
public:
    Vector2D position;
    Vector2D direction;
    Vector2D cameraPlane;

    Player(Vector2D position, Vector2D direction, Vector2D cameraPlane);
    void handleMovement(float moveSpeed, float turnSpeed, double secondsElapsed);
    void move(const Vector2D& movement);
    void rotate(double angleInRadians);
};

} // raycaster

#endif //PLAYER_H
