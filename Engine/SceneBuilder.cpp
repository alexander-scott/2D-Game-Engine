#include "SceneBuilder.h"

#include "ComponentBuilder.h"

#include "BuildSceneMessage.h"
#include "RequestBuildSceneMessage.h"

#include <fstream>

#include "Logger.h"

SceneBuilder::SceneBuilder(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
	: ISystem(SystemType::eSceneBuilder, dispatcher){ }

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
		shared_ptr<Scene> scene = BuildScene(msg.FilePath);

		// Send built scene to SceneManager system
		BuildSceneMessage sceneMsg(scene);
		SendMessageToDispatcher(sceneMsg);
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
	ComponentBuilder componentBuilder;

	// Build the gameobjects
	xml_node<>* gameObjectNode = root->first_node("GameObject");
	while (gameObjectNode)
	{
		string tag = gameObjectNode->first_attribute("tag")->value();
		GUID guid = StringToGUID(string(gameObjectNode->first_attribute("guid")->value()));

		auto gameObject = GameObject::MakeGameObject(tag, guid);

		// Create this gameobjects components
		xml_node<>* component = gameObjectNode->first_node("Component");
		while (component)
		{
			IComponent* newComponent = componentBuilder.BuildComponent(component);
			gameObject->AddComponent(newComponent);

			component = component->next_sibling("Component");
		}

		scene->AddGameObject(gameObject);

		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	return scene;
}

GUID SceneBuilder::StringToGUID(const std::string& guid) {
	GUID output;
	unsigned long p0;
	int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

	int err = sscanf_s(guid.c_str(), "%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10);

	if (err != 11)
		throw std::logic_error("Invalid GUID, format should be {00000000-0000-0000-0000-000000000000}");

	// Set the data like this to avoid corrupting the stack
	output.Data1 = p0;
	output.Data2 = p1;
	output.Data3 = p2;
	output.Data4[0] = p3;
	output.Data4[1] = p4;
	output.Data4[2] = p5;
	output.Data4[3] = p6;
	output.Data4[4] = p7;
	output.Data4[5] = p8;
	output.Data4[6] = p9;
	output.Data4[7] = p10;
	return output;
}