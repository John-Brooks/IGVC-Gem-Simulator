#pragma once
#include "ScenarioObject.h"
#include <memory>

class SimulationObject : public ScenarioObject
{
public:
	virtual void ProcessSimulationTimeStep(double time_step){};

	virtual void UpdatePoseTransformedDrawable() {
		mPoseTransformedDrawable->mLines = mLines;
		for (auto& line : mPoseTransformedDrawable->mLines)
		{
			ApplyObjectPose(line, mPose);
		}
	}

	std::shared_ptr<DrawableObject> mPoseTransformedDrawable = std::make_shared< DrawableObject >();

protected:
	//Derived implementations should call this after creating the base geometry
	virtual void InitPoseTransformedDrawable()
	{
		*mPoseTransformedDrawable = *static_cast<DrawableObject*>(this);
	}

};