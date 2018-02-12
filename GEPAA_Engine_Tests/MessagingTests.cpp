#include "CppUnitTest.h"

#include "../Engine/SystemMessageDispatcher.h"

#include "../Engine/SceneManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{
	class SceneManagerFixture : public SceneManager
	{
	public:
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
			SystemMessageDispatcher systemMessageDispatcher;

			auto sceneManager = make_unique<SceneManagerFixture>();

			// Add listener
			systemMessageDispatcher.AddListener(sceneManager._Myptr(), SystemMessageType::eDrawScene);

			// Send message
			systemMessageDispatcher.SendMessageToListeners(ISystemMessage(SystemMessageType::eDrawScene));
		
			// Test the system recieved the correct message type
			Assert::IsTrue(sceneManager->RecievedMessage);
		}
	};
}