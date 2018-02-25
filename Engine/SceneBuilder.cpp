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

#pragma warning( push )
#pragma warning( disable : 4477)

std::string guidToString(GUID guid) {
	std::array<char, 40> output;
	snprintf(output.data(), output.size(), "{%08X-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	return std::string(output.data());
}

GUID stringToGUID(const std::string& guid) {
	GUID output;
	const auto ret = sscanf_s(guid.c_str(), "{%8X-%4hX-%4hX-%2hX%2hX-%2hX%2hX%2hX%2hX%2hX%2hX}", &output.Data1, &output.Data2, &output.Data3, &output.Data4[0], &output.Data4[1], &output.Data4[2], &output.Data4[3], &output.Data4[4], &output.Data4[5], &output.Data4[6], &output.Data4[7]);
	if (ret != 11)
		throw std::logic_error("Unvalid GUID, format should be {00000000-0000-0000-0000-000000000000}");
	return output;
}

#pragma warning( pop ) 

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
		string guids = string(gameObjectNode->first_attribute("guid")->value());

		GUID test = stringToGUID(guids);

		auto gameObject = GameObject::MakeGameObject(tag);

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