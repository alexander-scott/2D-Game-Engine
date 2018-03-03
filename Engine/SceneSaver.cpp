#include "SceneSaver.h"

#include "ComponentSaver.h"

#include "SaveSceneMessage.h"

#include <fstream>

SceneSaver::SceneSaver(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: ISystem(SystemType::eSceneSaver, dispatcher)
{
	
}

void SceneSaver::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eSaveSceneMessage);
}

void SceneSaver::RecieveMessage(ISystemMessage & message)
{
	if (message.Type == SystemMessageType::eSaveSceneMessage)
	{
		SaveSceneMessage& msg = static_cast<SaveSceneMessage&>(message);
		SaveScene(msg.GetScene(), msg.GetFilePath());
	}
}

void SceneSaver::SaveScene(shared_ptr<Scene> scene, string filePath)
{
	std::ofstream theFile(filePath);

	xml_document<> doc;
	xml_node<>* decl = doc.allocate_node(node_declaration);
	doc.append_node(decl);

	// Create root node (SCENE)
	xml_node<>* root = doc.allocate_node(node_element, "scene");
	root->append_attribute(doc.allocate_attribute("name", doc.allocate_string(scene->GetSceneName().c_str())));
	doc.append_node(root);

	ComponentSaver componentSaver;

	// For every gameobject in the scene
	for (int i = 0; i < scene->GetNumberOfGameObjects(); i++)
	{
		xml_node<>* gameObject = doc.allocate_node(node_element, "GameObject");
		gameObject->append_attribute(doc.allocate_attribute("tag", doc.allocate_string(scene->GetGameObject(i)->GetTag().c_str())));
		gameObject->append_attribute(doc.allocate_attribute("guid", doc.allocate_string(GUIDToString(&scene->GetGameObject(i)->GetID()).c_str())));

		// For every component the gameobject has
		auto components = scene->GetGameObject(i)->GetAllComponents();
		for (int j = 0; j < components.size(); j++)
		{
			xml_node<>* component = doc.allocate_node(node_element, "Component");

			auto componentValues = componentSaver.SaveComponent(components[j]);
			for (auto value : componentValues)
			{
				component->append_attribute(doc.allocate_attribute(doc.allocate_string(value.first.c_str()), doc.allocate_string(value.second.c_str())));
			}

			gameObject->append_node(component);
		}

		root->append_node(gameObject);
	}

	theFile << doc;
	theFile.close();
	doc.clear();
}

std::string SceneSaver::GUIDToString(GUID *guid) 
{
	char guid_string[37]; // 32 hex chars + 4 hyphens + null terminator
	snprintf(
		guid_string, sizeof(guid_string) / sizeof(guid_string[0]),
		"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		guid->Data1, guid->Data2, guid->Data3,
		guid->Data4[0], guid->Data4[1], guid->Data4[2],
		guid->Data4[3], guid->Data4[4], guid->Data4[5],
		guid->Data4[6], guid->Data4[7]);
	return guid_string;
}
