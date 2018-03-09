#include "CppUnitTest.h"

#include "../Engine/Engine.h"
#include "../Engine/SceneManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{
	class SceneManagerFixture : public SceneManager
	{

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
			Engine engine;

			// Create scene
			auto scene = make_shared<Scene>(string("TEST CENE"));
			auto gameObject = GameObject::MakeGameObject("TEST GAME OBJECT");

			auto sceneManager = dynamic_pointer_cast<SceneManager>(engine.GetSystem(SystemType::eSceneManager));
			
			
			//sceneManager->
		}
	};
}