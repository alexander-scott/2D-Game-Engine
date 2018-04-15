#include "CppUnitTest.h"

#include "../Engine/Engine.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ComponentFactory.h"
#include "../Engine/BuildSceneMessage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{
	// This is a workaround to return the current directory. 
	// Normal method doesn't seem to work during tests.
	// However this workaround will not work if unit tests aren't run on the same machine
	// as they are built.
#define TEST_CASE_DIRECTORY GetDirectoryName2(__FILE__)

	string GetDirectoryName2(string path)
	{
		size_t last_slash_idx = path.rfind("\\");
		if (std::string::npos != last_slash_idx)
		{
			path = path.substr(0, last_slash_idx); // Remove the file name
		}

		last_slash_idx = path.rfind("\\");
		if (std::string::npos != last_slash_idx)
		{
			path = path.substr(0, last_slash_idx + 1); // Remove the GEPAA_Engine_Tests folder
			return path;
		}

		return "";
	}

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
		EngineFixture1() : Engine(std::string(TEST_CASE_DIRECTORY + "Resources"))
		{
			InitaliseSystems();
		}
	};

	class EngineFixture2 : public Engine
	{
	public:
		EngineFixture2() : Engine(std::string(TEST_CASE_DIRECTORY + "Resources"))
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

			Assert::AreEqual(0, sceneManager->DrawCount);
			Assert::AreEqual(0, sceneManager->UpdateCount);

			int loopCount = 0;
			while (loopCount < 1) // FIX THIS
			{
				engine.Update();
				loopCount++;
				Sleep(100);
			}

			// Draw count should have incremented
			Assert::AreNotEqual(0, sceneManager->DrawCount);

			// Update count should have incremented
			Assert::AreNotEqual(0, sceneManager->UpdateCount);

			// Update count should have incremented much more than draw count
			// as there's a limit on how often the scene can draw
			Assert::AreNotEqual(sceneManager->DrawCount, sceneManager->UpdateCount);
		}
	};
}