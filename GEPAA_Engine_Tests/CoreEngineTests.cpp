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

		}

		void RecieveMessage(ISystemMessage& message) override
		{
			SceneManager::RecieveMessage(message);
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

	class EngineFixture : public Engine
	{
	public:
		EngineFixture()
		{
			_messageDispatcher = make_shared<SystemMessageDispatcher>();
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
			Engine engine;
			// Test that engine gets created without any crashes
		}

		TEST_METHOD(CoreEngineUpdateLoop)
		{
			// Create engine
			EngineFixture engine = EngineFixture();

			auto scene = make_shared<Scene>(string("TEST SCENE")); // Create scene
			auto gameObject = GameObject::MakeGameObject("TEST GAME OBJECT"); // Create test GO
			auto transComponent = ComponentFactory::MakeTransformComponent(Vec2(0, 0), 0, 1); // Add trans component
			gameObject->AddComponent(transComponent);
			scene->AddGameObject(gameObject);

			// Get scene manager and set current scene
			auto sceneManager = dynamic_pointer_cast<SceneManagerFixture>(engine.GetSystem(SystemType::eSceneManager));
			BuildSceneMessage msg(scene);
			sceneManager->RecieveMessage(msg);

			int loopCount = 0;
			while (loopCount < 1000)
			{
				engine.Update();
				Sleep(1);
				loopCount++;
			}

			Assert::AreNotEqual(0, sceneManager->DrawCount);
			Assert::AreNotEqual(0, sceneManager->UpdateCount);
		}
	};
}