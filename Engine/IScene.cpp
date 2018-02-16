#include "IScene.h"

IScene::IScene(std::string sceneName) : _sceneName(sceneName) { }

IScene::~IScene()
{
	for (auto go : _gameObjects)
	{
		go = nullptr;
	}
}

void IScene::Draw(DrawSceneMessage& message)
{
	map<int, vector<shared_ptr<GameObject>>>::iterator renderLayer;
	// Render all GameObjects at each render layer
	for (renderLayer = _renderLayers.begin(); renderLayer != _renderLayers.end(); renderLayer++)
	{
		for (int i = 0; i < renderLayer->second.size(); i++)
		{
			renderLayer->second[i]->Draw(message);
		}
	}
}

void IScene::Update(float deltaTime)
{
	for (auto go : _gameObjects)
	{
		go->Update(deltaTime);
	}
}

void IScene::SendMessageToGameObjects(IComponentMessage & message)
{
	for (auto go : _gameObjects)
	{
		go->SendMessageToComponent(message);
	}
}

// In this function you can dissassemble GameObjects and add them to various structures, 
// e.g. if the GameObject has a IDrawableComponent component add it to renderLayer structure.
// Only called at scene initalisation so doesn't have to be performant
void IScene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);

	_gameObjectIDs.insert(make_pair(gameObject->GetID(), gameObject));

	for (auto component : gameObject->GetAllComponents())
	{
		IDrawableComponent * drawableComponent = dynamic_cast<IDrawableComponent *> (component);

		if (drawableComponent != nullptr)
		{
			_renderLayers[drawableComponent->RenderLayer].push_back(gameObject);
		}
	}
};
