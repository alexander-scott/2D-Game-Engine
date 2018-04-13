#include "CppUnitTest.h"

#include "..\Engine\SceneBuilder.h"
#include "..\Engine\TransformComponent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{		
	// This is a workaround to return the current directory. 
	// Normal method doesn't seem to work during tests.
	// However this workaround will not work if unit tests aren't run on the same machine
	// as they are built.
	#define TEST_CASE_DIRECTORY GetDirectoryName(__FILE__)

	string GetDirectoryName(string path)
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

	// Build an instance of the class that can access protected methods
	class SceneBuilderFixture : public SceneBuilder
	{
	public:
		SceneBuilderFixture(shared_ptr<SystemMessageDispatcher> dispatcher) : SceneBuilder(dispatcher) { }

		shared_ptr<Scene> TestBuildScene(std::string path)
		{
			return BuildScene(path);
		}
	};

	TEST_CLASS(SceneBuilderTests)
	{
	public:

		TEST_METHOD(SceneBuilderBuildScene)
		{
			auto dispatcher = make_shared<SystemMessageDispatcher>();
			SceneBuilderFixture sceneBuilder(dispatcher);
			auto scene = sceneBuilder.TestBuildScene(std::string(GetDirectoryName(TEST_CASE_DIRECTORY)) 
				+ std::string("Resources\\Scenes\\TestScene.xml"));
		
			// Test scene is not null and scene name is correct
			Assert::AreEqual(scene->GetSceneName(), std::string("testscene"));

			// Test GameObject successfully created
			Assert::AreEqual(scene->GetNumberOfGameObjects(), 1);

			// Test GameObject name is correct
			Assert::AreEqual(scene->GetGameObject(0)->GetTag(), std::string("TestGameObject"));

			// Test Component has been built and added to GameObject
			Assert::AreEqual(scene->GetGameObject(0)->GetAllComponents().size(), (size_t)1);

			// Test Component values have been successfully set
			Assert::AreEqual(scene->GetGameObject(0)->GetComponent<TransformComponent>()->GetWorldPosition().x, (float)17);
		}
	};
}