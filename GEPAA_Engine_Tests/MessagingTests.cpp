#include "CppUnitTest.h"

#include "../Engine/SceneManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{
	class SceneManagerFixture : public SceneManager
	{
	public:
		SceneManagerFixture(shared_ptr<SystemMessageDispatcher> dispatcher) : SceneManager(dispatcher) { }

		void RecieveMessage(ISystemMessage& message) override
		{
			if (message.Type == SystemMessageType::eDrawScene)
			{
				RecievedMessage = true;
			}
		}

		bool RecievedMessage = false;
	};

	TEST_CLASS(MessagingTests)
	{
		TEST_METHOD(MessageSend)
		{
			auto dispatcher = make_shared<SystemMessageDispatcher>();

			auto sceneManager = make_unique<SceneManagerFixture>(dispatcher);

			// Add listener
			dispatcher->AddListener(sceneManager._Myptr(), SystemMessageType::eDrawScene);

			// Send message
			dispatcher->SendMessageToListeners(ISystemMessage(SystemMessageType::eDrawScene));
		
			// Test the system recieved the correct message type
			Assert::IsTrue(sceneManager->RecievedMessage);
		}
	};
}