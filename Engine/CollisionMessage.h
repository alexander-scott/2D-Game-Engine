#pragma once

#include "IComponentMessage.h"

#include <memory>

class GameObject;

class CollisionMessage : public IComponentMessage
{
public:
	CollisionMessage(std::shared_ptr<GameObject> collidedObj, std::string gameObjectTag)
		: IComponentMessage(ComponentMessageType::eCollisionMessage)
	{
		CollidedObject = collidedObj;
		CollidedObjectTag = gameObjectTag;
	}

	std::shared_ptr<GameObject> CollidedObject;
	std::string					CollidedObjectTag;
};