#include "SceneBuilder.h"

#include "ComponentBuilder.h"

#include "BuildSceneMessage.h"
#include "RequestBuildSceneMessage.h"

#include <fstream>

SceneBuilder::SceneBuilder(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
	: ISystem(SystemType::eSceneBuilder, dispatcher), SystemMessageMessenger(dispatcher) { }

void SceneBuilder::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eRequestBuildSceneMessage);
}

void SceneBuilder::RecieveMessage(ISystemMessage & message)
{
	if (message.Type == SystemMessageType::eRequestBuildSceneMessage)
	{
		RequestBuildSceneMessage& msg = static_cast<RequestBuildSceneMessage&>(message);

		// If the engine asks the SceneBuilder system to create a Scene, build one and send a pointer to it in a message.
		shared_ptr<IScene> scene = BuildScene(msg.FilePath);

		// Send built scene to SceneManager system
		BuildSceneMessage sceneMsg(scene);
		SendMessageToDispatcher(sceneMsg);
	}
}

shared_ptr<IScene> SceneBuilder::BuildScene(string filePath)
{
	//Loads a level from xml file
	//Load the file
	ifstream inFile(filePath);

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

	// Initalise the scene
	auto scene = make_shared<IScene>(string(root->first_attribute("name")->value()));

	// Build the gameobjects
	xml_node<>* gameObjectNode = root->first_node("GameObject");
	while (gameObjectNode)
	{
		auto gameObject = GameObject::MakeGameObject(gameObjectNode->first_attribute("tag")->value());

		// Create this gameobjects components
		xml_node<>* component = gameObjectNode->first_node("Component");
		while (component)
		{
			IComponent* newComponent = ComponentBuilder::BuildComponent(component);
			gameObject->AddComponent(newComponent);

			component = component->next_sibling("Component");
		}

		scene->AddGameObject(gameObject);

		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	return scene;
}