//
// Created by ruairi on 01/08/2025.
//

#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>

namespace raycaster
{
    class Vector2D {
    public:

        double x;
        double y;
        Vector2D() = default;

        Vector2D(const Vector2D& vec)
        {
            x = vec.x;
            y = vec.y;
        }

        Vector2D(double x, double y){
            this->x = x;
            this->y = y;
        };

        [[nodiscard]] double magnitude() const{
            return sqrt(pow((x), 2) + pow((y), 2));
        };

        //Operator Overloading
        Vector2D operator+(const Vector2D& other) const{
            return {x + other.x, y + other.y};
        }

        Vector2D operator-(const Vector2D& other) const{
            return {x - other.x, y - other.y};
        }

        Vector2D operator*(const double scalar) const{
            return {x * scalar, y * scalar};
        }

        Vector2D& operator+= (const Vector2D other){
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2D& operator-= (const Vector2D other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2D& rotate(const double angleInRadians){
            const double sinTheta = sin(angleInRadians);
            const double cosTheta = cos(angleInRadians);
            //Below is some hardcoded Matrix multiplication. Vector is pre-multiplied by [cos(θ) -sin(θ)   sin(θ) cos(θ)]
            const double newX = x * cosTheta - y * sinTheta;
            const double newY = x * sinTheta + y * cosTheta;
            x = newX;
            y = newY;
            return *this;
        }

        Vector2D& normalise(){
            const double length = magnitude();
            x /= length;
            y /= length;
            return *this;
        }

        [[nodiscard]] inline Vector2D floor() const
        {
            return {std::floor(x), std::floor(y)};
        }

    };

    inline Vector2D operator*(const float scalar, const Vector2D& v) {
        return {v.x * scalar, v.y * scalar};
    }

    static double dot(const Vector2D& a, const Vector2D& b)
    {
        return a.x * b.x + a.y * b.y;
    }



}
#endif //VECTOR2D_H
