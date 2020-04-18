#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(Line line)
{
    SetupFromLine(line);
    mDrawable = std::make_shared<DrawableObject>(line);
    mType = ObjectType::VehicleDistanceSensor;

    mPoseTransformedDrawable->mColor.r = 30;
    mPoseTransformedDrawable->mColor.g = 30;
    mPoseTransformedDrawable->mColor.b = 255;
}
void DistanceSensor::ProcessSimulationTimeStep(double time_step)
{
    mPoseTransformedDrawable->mPose = mPose;
    UpdatePoseTransformedDrawable();
    *mDrawable = *mPoseTransformedDrawable;
    mDistance = mLength;
}
double DistanceSensor::ProcessCollision(const CollisionDetection& collisions)
{
    if( collisions.collision_points.size() != collisions.collidided_objs.size() ||
        mPoseTransformedDrawable->mLines.size() != 1)
    {
        printf("Error calculating sensor distance.\n");
        return -1;
    }

    std::shared_ptr< ScenarioObject > closest_object = nullptr;
    double closest_distance = mLength;
    Point& my_origin = mPoseTransformedDrawable->mLines[0].p1;
    Point& my_end = mPoseTransformedDrawable->mLines[0].p2;
    Point closest_point = my_end;
    double x = my_end.x - my_origin.x;
    double y = my_end.y - my_origin.x;
    double distance;

    for(int i = 0; i < collisions.collision_points.size(); i++)
    {
        const auto& obj = collisions.collidided_objs[i];
        const auto& point = collisions.collision_points[i];

        //Only process certain collisions
        switch( obj->mType )
        {
            case ObjectType::LaneLine:
                break;
            default:
                continue;
        }

        x = point.x - mPoseTransformedDrawable->mLines[0].p1.x;
        y = point.y - mPoseTransformedDrawable->mLines[0].p1.y;
        distance = sqrt( pow(x, 2) + pow(y, 2) );

        if( distance < closest_distance )
        {
            closest_distance = distance;
            closest_object = obj;
            closest_point = point;
        }
    }


    mDrawable->mLines[0].p2 = closest_point;

    mDistance = closest_distance;

    return closest_distance;
}