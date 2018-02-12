#include "CppUnitTest.h"

#include "../Engine/GameObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{
	TEST_CLASS(GameObjectTests)
	{
		TEST_METHOD(GameObjectBuild)
		{
			auto gameObject = GameObject::MakeGameObject("testgameobject");

			// Test game object gets created and tag is correct
			Assert::AreEqual(gameObject->GetTag(), std::string("testgameobject"));
		}

		TEST_METHOD(GameObjectAddRemoveComponent)
		{
			auto gameObject = GameObject::MakeGameObject("testgameobject");
			auto component = ComponentFactory::MakeTransformComponent(Vec2(0, 0), 0.0f, 0.0f);
			gameObject->AddComponent(component);

			// Test component is added
			Assert::AreEqual(gameObject->GetAllComponents().size(), (size_t)1);

			gameObject->RemoveComponent<TransformComponent>();

			// Test component is removed
			Assert::AreEqual(gameObject->GetAllComponents().size(), (size_t)0);
		}

		TEST_METHOD(GameObjectGetComponent)
		{
			auto gameObject = GameObject::MakeGameObject("testgameobject");
			auto component = ComponentFactory::MakeTransformComponent(Vec2(0, 0), 0.0f, 0.0f);
			gameObject->AddComponent(component);

			// Get transform component
			TransformComponent* transform = gameObject->GetComponent<TransformComponent>();
			transform->SetActive(false);

			// Get it again and check if the change has persisted
			TransformComponent* trans = gameObject->GetComponent<TransformComponent>();

			// Test GetComponent works and can change a variable through it
			Assert::IsFalse(trans->GetActive());
		}

		TEST_METHOD(GameObjectSetParent)
		{
			auto gameObject1 = GameObject::MakeGameObject("childgameobject");
			auto component1 = ComponentFactory::MakeTransformComponent(Vec2(0, 0), 0.0f, 0.0f);
			gameObject1->AddComponent(component1);

			auto gameObject2 = GameObject::MakeGameObject("parentgameobject");
			auto component2 = ComponentFactory::MakeTransformComponent(Vec2(0, 0), 0.0f, 0.0f);
			gameObject2->AddComponent(component2);

			// Set GameObject1 parent
			gameObject1->SetParent(gameObject2);

			// Test parent is set
			Assert::AreEqual(gameObject1->GetParent()->GetTag(), std::string("parentgameobject"));

			// Test child is set for parent
			Assert::AreEqual(gameObject2->GetChildren().size(), (size_t)1);
		}
	};
}
