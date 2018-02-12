#include "CppUnitTest.h"

#include "..\Engine\SceneBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{		
	// Build an instance of the class that can access protected methods
	class SceneBuilderFixture : public SceneBuilder
	{
	public:
		shared_ptr<IScene> TestBuildScene(std::string path)
		{
			return BuildScene(path);
		}
	};

	TEST_CLASS(SceneBuilderTests)
	{
	public:

		TEST_METHOD(SceneBuilderBuildScene)
		{
			SceneBuilderFixture sceneBuilder; // Remove hardcoded path
			auto scene = sceneBuilder.TestBuildScene("C:\\Users\\Alex\\Dropbox\\University Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\Semester 2\\gepaa-group-1\\GEPAA_Engine_Tests\\TestResources\\TestScene.xml");
		
			// Test scene is not null and scene name is correct
			Assert::AreEqual(scene->GetSceneName(), std::string("testscene"));

			// Test GameObject successfully created
			Assert::AreEqual(scene->GetNumberOfGameObjects(), 1);

			// Test GameObject name is correct
			Assert::AreEqual(scene->GetGameObjectAtIndex(0)->GetTag(), std::string("TestGameObject"));

			// Test Component has been built and added to GameObject
			Assert::AreEqual(scene->GetGameObjectAtIndex(0)->GetAllComponents().size(), (size_t)1);
		}
	};
}