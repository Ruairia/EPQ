//
// Created by ruairi on 03/08/2025.
//

#ifndef RAY_H
#define RAY_H
#include "Vector2D.h"

namespace raycaster
{
    class Ray {
    public:
        Ray(const Vector2D origin, const Vector2D direction, const Vector2D position,
            const Vector2D rayPathDistanceForGridStep, const Vector2D rayCumulativeDistance, const Vector2D step)
        {
            this->origin = origin;
            this->direction = direction;
            this->position = position;
            this->rayPathDistanceForGridStep = rayPathDistanceForGridStep;
            this->rayCumulativeDistance = rayCumulativeDistance;
            this->step = step;
        }
        Vector2D origin;
        Vector2D direction;
        Vector2D position;
        Vector2D rayPathDistanceForGridStep;
        Vector2D rayCumulativeDistance;
        Vector2D step;
    };
}
#endif //RAY_H
