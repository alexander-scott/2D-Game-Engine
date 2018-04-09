#include "CppUnitTest.h"

#include "../Engine/Engine.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ComponentFactory.h"
#include "../Engine/BuildSceneMessage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{
	class SceneManagerFixture : public SceneManager
	{
	public:
		SceneManagerFixture(std::shared_ptr<SystemMessageDispatcher> dispatcher)
			: SceneManager(dispatcher)
		{
			InitaliseListeners();
		}

		void InitaliseListeners() override
		{
			SubscribeToMessageType(SystemMessageType::eDrawScene);
			SubscribeToMessageType(SystemMessageType::eUpdateScene);
		}

		void RecieveMessage(ISystemMessage& message) override
		{
			switch (message.Type)
			{
			case SystemMessageType::eDrawScene:
				DrawCount++;
				break;

			case SystemMessageType::eUpdateScene:
				UpdateCount++;
				break;
			}
		}

		int DrawCount = 0;
		int UpdateCount = 0;
	};

	class EngineFixture1 : public Engine
	{
	public:
		EngineFixture1()
		{
			InitaliseSystems();
		}
	};

	class EngineFixture2 : public Engine
	{
	public:
		EngineFixture2()
		{
			auto sceneManager = make_shared<SceneManagerFixture>(_messageDispatcher);
			_systems.insert(std::make_pair(sceneManager->SysType, sceneManager));
		}

		void Update()
		{
			UpdateLoop();
		}
	};

	TEST_CLASS(CoreEngineTests)
	{
	public:
		TEST_METHOD(CoreEngineBuildEnigne)
		{
			EngineFixture1 engine;
			// Test that engine gets created without any crashes
		}

		TEST_METHOD(CoreEngineUpdateLoop)
		{
			// Create engine
			EngineFixture2 engine;

			auto scene = make_shared<Scene>(string("TEST SCENE")); // Create scene
			auto gameObject = GameObject::MakeGameObject("TEST GAME OBJECT"); // Create test GO
			auto transComponent = ComponentFactory::MakeTransformComponent(Vec2(0, 0), 0, 1); // Add trans component
			gameObject->AddComponent(transComponent);
			scene->AddGameObject(gameObject);

			// Get scene manager and set current scene
			auto sceneManager = dynamic_pointer_cast<SceneManagerFixture>(engine.GetSystem(SystemType::eSceneManager));

			int loopCount = 0;
			/*while (loopCount < 10) // FIX THIS
			{
				engine.Update();
				loopCount++;
			}*/

			Assert::AreNotEqual(0, sceneManager->DrawCount);
			Assert::AreNotEqual(0, sceneManager->UpdateCount);
		}
	};
}