#include "SceneBuilder.h"

#include "ComponentBuilder.h"

#include "BuildSceneMessage.h"
#include "RequestBuildSceneMessage.h"
#include <fstream>

#include "Logger.h"

SceneBuilder::SceneBuilder(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
	: ISystem(SystemType::eSceneBuilder, dispatcher)
{ 
	_currentFilePath = "";
}

void SceneBuilder::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eRequestBuildSceneMessage);
	SubscribeToMessageType(SystemMessageType::ePlayStopped);
}

void SceneBuilder::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
		case SystemMessageType::eRequestBuildSceneMessage:
		{
			RequestBuildSceneMessage& msg = static_cast<RequestBuildSceneMessage&>(message);

			// If the engine asks the SceneBuilder system to create a Scene, build one and send a pointer to it in a message.
			shared_ptr<Scene> scene = BuildScene(msg.FilePath);
			_currentFilePath = msg.FilePath;

			// Send built scene to SceneManager system
			BuildSceneMessage sceneMsg(scene);
			SendMessageToDispatcher(sceneMsg);
			break;
		}
		case SystemMessageType::ePlayStopped:
		{
			if (_currentFilePath == "")
				throw std::exception("Current file path is empty");

			// If the engine asks the SceneBuilder system to create a Scene, build one and send a pointer to it in a message.
			shared_ptr<Scene> scene = BuildScene(_currentFilePath);

			// Send built scene to SceneManager system
			BuildSceneMessage sceneMsg(scene);
			SendMessageToDispatcher(sceneMsg);
			break;
		}
	}
}

shared_ptr<Scene> SceneBuilder::BuildScene(string filePath)
{
	//Loads a level from xml file
	//Load the file
	ifstream inFile(filePath);

	if (!inFile)
	{
		Logger::Instance().LogMessage("Could not load XML file!", "SCENE_BUILDER", LogSeverity::eError);
		throw std::exception("Could not load XML file!");
	}

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

	auto scene = make_shared<Scene>(string(root->first_attribute("name")->value()));

	// Build the gameobjects
	xml_node<>* gameObjectNode = root->first_node("GameObject");
	while (gameObjectNode)
	{
		string tag = gameObjectNode->first_attribute("tag")->value();
		GUID guid = ComponentBuilder::StringToGUID(string(gameObjectNode->first_attribute("guid")->value()));

		scene->AddGameObject(GameObject::MakeGameObject(tag, guid));
		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	ComponentBuilder componentBuilder(scene);

	// Add the components to the gameobjects
	gameObjectNode = root->first_node("GameObject");
	while (gameObjectNode)
	{
		GUID guid = ComponentBuilder::StringToGUID(string(gameObjectNode->first_attribute("guid")->value()));
		auto gameObject = scene->GetGameObject(guid);

		// Create this gameobjects components
		xml_node<>* componentNode = gameObjectNode->first_node("Component");
		while (componentNode)
		{
			IComponent* newComponent = componentBuilder.BuildComponent(componentNode);
			gameObject->AddComponent(newComponent);

			componentNode = componentNode->next_sibling("Component");
		}

		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	// Fetch all componentNode dependencies
	gameObjectNode = root->first_node("GameObject");
	while (gameObjectNode)
	{
		GUID guid = ComponentBuilder::StringToGUID(string(gameObjectNode->first_attribute("guid")->value()));
		auto gameObject = scene->GetGameObject(guid);

		xml_node<>* componentNode = gameObjectNode->first_node("Component");
		int index = 0;
		while (componentNode)
		{
			IComponent* component = gameObject->GetComponentAtIndex(index);

			xml_node<>* dependencyNode = componentNode->first_node("Dependency");
			if (dependencyNode) // If this component has dependencies
			{
				map<string, GUID> dependecies; // Gather all dependencies
				for (const xml_attribute<>* attribute = dependencyNode->first_attribute(); attribute; attribute = attribute->next_attribute()) 
				{
					dependecies.insert(make_pair(attribute->name(), ComponentBuilder::StringToGUID(string(attribute->value()))));
				}

				// Build the dependencies
				componentBuilder.BuildComponentDependecies(component, &dependecies); 
			}

			componentNode = componentNode->next_sibling("Component");
			index++;
		}

		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	// Add parents to the gameobjects
	gameObjectNode = root->first_node("GameObject");
	while (gameObjectNode)
	{
		GUID guid = ComponentBuilder::StringToGUID(string(gameObjectNode->first_attribute("guid")->value()));
		auto gameObject = scene->GetGameObject(guid);

		// Check if the GameObject has a parent
		if (gameObjectNode->first_attribute("parent"))
		{
			GUID parentGuid = ComponentBuilder::StringToGUID(string(gameObjectNode->first_attribute("parent")->value()));
			auto parentGO = scene->GetGameObject(parentGuid);
			gameObject->SetParent(parentGO);
		}

		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	return scene;
}
