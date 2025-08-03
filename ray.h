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
        Ray() = default;
        Ray(Vector2D origin, Vector2D direction)
        {
            this->position = origin.floor();
            this->direction = direction;

            pathDistanceForGridStep.x = (direction.x == 0) ? 1e30 : abs(1 / direction.x);
            pathDistanceForGridStep.y = (direction.y == 0) ? 1e30 : abs(1 / direction.y);
            if (direction.x<0)
            {
                step.x = -1;
                cumulativeDistance.x = (origin.x - position.x) * pathDistanceForGridStep.x;
            }
            else
            {
                step.x = 1;
                cumulativeDistance.x = (position.x + 1 - origin.x) * pathDistanceForGridStep.x;
            }
            if (direction.y<0)
            {
                step.y = -1;
                cumulativeDistance.y = (origin.y - position.y) * pathDistanceForGridStep.y;
            }
            else
            {
                step.y = 1;
                cumulativeDistance.y = (position.y + 1 - origin.y) * pathDistanceForGridStep.y;
            }
        }
        Vector2D origin;
        Vector2D direction;
        Vector2D pathDistanceForGridStep;
        Vector2D cumulativeDistance;
        Vector2D step;
        Vector2D position;
        Vector2D mapPosition;
    };
}
#endif //RAY_H
