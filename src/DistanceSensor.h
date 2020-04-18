#pragma once

#include "SimulationObject.h"
#include "Collision.h"

class DistanceSensor : public SimulationObject
{
public:
    DistanceSensor(Line line);
    void ProcessSimulationTimeStep(double time_step);
    double ProcessCollision(const CollisionDetection& collisions);
    void SetLength(double length) {mLength = length;}
    void SetAngle(double angle) {mAngle = angle;}
    double GetAngle() const {return mAngle;}
    double GetLength() const {return mLength;}

    

    std::shared_ptr< DrawableObject > mDrawable;
    double mDistance;

private:
    double mLength;
    double mAngle;
};

