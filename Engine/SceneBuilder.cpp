#include "SceneBuilder.h"

#include "BuildSceneMessage.h"
#include "RequestBuildSceneMessage.h"

SceneBuilder::SceneBuilder() : ISystem(SystemType::eSceneBuilder)
{
	SubscribeToMessageType(SystemMessageType::eRequestBuildSceneMessage);
}

void SceneBuilder::RecieveMessage(ISystemMessage & message)
{
	if (message.Type == SystemMessageType::eRequestBuildSceneMessage)
	{
		RequestBuildSceneMessage& msg = static_cast<RequestBuildSceneMessage&>(message);

		// If the engine asks the SceneBuilder system to create a Scene, build one and send a pointer to it in a message.
		shared_ptr<IScene> scene = BuildTestScene(msg.FilePath);

		// Send built scene to SceneManager system
		BuildSceneMessage sceneMsg(scene);
		SystemMessageDispatcher::Instance().SendMessageToListeners(sceneMsg);
	}
}

shared_ptr<IScene> SceneBuilder::BuildTestScene(string filePath)
{
	// BUILD AND RETURN AN EMPTY ISCENE FOR NOW. IN FUTURE PARSE SCENE FILES AND BUILD SCENE FROM THERE.
	auto scene = make_shared<IScene>("TestScene");
	
	auto testGameObject = GameObject::MakeGameObject("TestObject");
	scene->AddGameObject(testGameObject);

	return scene;
}

shared_ptr<IScene> SceneBuilder::BuildScene(string filePath)
{
	//Loads a level from xml file
	//Load the file
	ifstream inFile(filePath);

	if (!inFile)
		throw "Could not load file at path: " + filePath;

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

	auto scene = make_shared<IScene>(string(root->first_attribute("name")->value()));
	xml_node<>* gameObjectNode = root->first_node("GameObject");
	while (gameObjectNode)
	{
		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	return scene;
}