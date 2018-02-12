#include "CppUnitTest.h"

#include "..\Engine\SceneBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEPAA_Engine_Tests
{		
	// Build an instance of the class that can access protected methods
	class SceneBuilderFixture : public SceneBuilder
	{
	public:
		void TestOpenFile(std::string path)
		{
			//Load the file
			ifstream inFile(path);
			if (!inFile)
				throw std::exception("Could not load XML file!");

			//Dump contents of file into a string
			string xmlContents;

			//Blocked out of preference
			{
				string line;
				while (getline(inFile, line))
					xmlContents += line;
			}

			//Convert string to rapidxml readable char*
			vector<char> mXmlData = vector<char>(xmlContents.begin(), xmlContents.end());
			mXmlData.push_back('\0');

			//Create a parsed document with &xmlData[0] which is the char*
			xml_document<> doc;
			doc.parse<parse_no_data_nodes>(&mXmlData[0]);

			//Get the root node
			xml_node<>* root = doc.first_node();

			std::string sceneName = string(root->first_attribute("name")->value());
		}

		shared_ptr<IScene> TestBuildScene(std::string path)
		{
			return BuildScene(path);
		}
	};

	TEST_CLASS(SceneBuilderTests)
	{
	public:
		
		TEST_METHOD(SceneBuilderOpenFile)
		{
			SceneBuilderFixture sceneBuilder; // TODO: Remove hardcoded path
			sceneBuilder.TestOpenFile("C:\\Users\\Alex\\Dropbox\\University Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\Semester 2\\gepaa-group-1\\GEPAA_Engine_Tests\\TestResources\\TestScene.xml");
			
			// Test will pass if there is no error in the file open/read
		}

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