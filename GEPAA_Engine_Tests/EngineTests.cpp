#include "CppUnitTest.h"

#include "..\Engine\Engine.h"
#include "..\Engine\SceneManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{
	class SceneManagerFixtureEngine : public SceneManager
	{
	public:
		SceneManagerFixtureEngine(std::shared_ptr<SystemMessageDispatcher> dispatcher)
			: SceneManager(dispatcher)
		{

		}

		void RecieveMessage(ISystemMessage& message) override
		{
			switch (message.Type)
			{
				case SystemMessageType::eUpdateScene:
				{
					UpdateCount++;
					break;
				}
				case SystemMessageType::eDrawScene:
				{
					DrawCount++;
					break;
				}
			}
		}

		int UpdateCount = 0;
		int DrawCount = 0;
	};

	TEST_CLASS(EngineTests)
	{
		TEST_METHOD(EngineTestUpdateScene)
		{
			auto dispatcher = make_shared<SystemMessageDispatcher>();
			auto engine = make_shared<Engine>(dispatcher);
			auto sceneManager = make_shared<SceneManagerFixtureEngine>(dispatcher);

			engine->SubscribeToMessageType(SystemMessageType::eSystemUpdate);
			sceneManager->SubscribeToMessageType(SystemMessageType::eDrawScene);
			sceneManager->SubscribeToMessageType(SystemMessageType::eUpdateScene);

			int count = 0;
			while (count < 1000)
			{
				dispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eSystemUpdate));
				Sleep(1);
				count++;
			}

			// Test that Draw was called the exact number of times the loop was run
			Assert::AreEqual(sceneManager->DrawCount, 1000);

			// Test that Update was called at a fixed timestep
			// Resulting iN 137 in this case (DEPENDANT ON MS_PER_UPDATE AND LOOP SLEEP TIME)
			Assert::AreNotEqual(sceneManager->UpdateCount, 137);
		}
	};
}