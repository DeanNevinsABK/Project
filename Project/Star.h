#pragma once
#include "PlacableActor.h"

class Star : public PlacableActor
{
public:
	Star(int x, int y, ActorColor color)
		: PlacableActor(x, y, color)
	{

	}

	virtual ActorType GetType() override { return ActorType::Star; }
	virtual void Draw() override;
};