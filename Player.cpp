//
// Created by ruairi on 03/08/2025.
//

#include "Player.h"

#include <raylib.h>

namespace raycaster {

    Player::Player(const Vector2D& position, const Vector2D& direction, const Vector2D& cameraPlane)
    : position(position), direction(direction), cameraPlane(cameraPlane) {}

void Player::move(const Vector2D& movement) {
    position += movement;
}

void Player::rotate(double angleInRadians) {
    direction.rotate(angleInRadians);
    cameraPlane.rotate(angleInRadians);
}
    void Player::handleMovement(const float moveSpeed, const float turnSpeed, const double secondsElapsed)
{
    if (IsKeyDown(KEY_W))
    {
        move(moveSpeed * direction * secondsElapsed);
    }
    if (IsKeyDown(KEY_S))
    {
        move(-moveSpeed * direction * secondsElapsed);
    }
    if (IsKeyDown(KEY_D))
    {
        rotate(turnSpeed * secondsElapsed);
    }
    if (IsKeyDown(KEY_A))
    {
        rotate(-turnSpeed * secondsElapsed);
    }
}

} // raycaster