#include "IScene.h"

void IScene::Draw()
{
	map<int, vector<shared_ptr<GameObject>>>::iterator renderLayer;

	// Render all GameObjects at each render layer
	for (renderLayer = _renderLayers.begin(); renderLayer != _renderLayers.end(); renderLayer++)
	{
		for (int i = 0; i < renderLayer->second.size(); i++)
		{
			renderLayer->second[i]->Draw();
		}
	}
}

void IScene::Update(float deltaTime)
{
	// Update gameobjects
	for (auto go : _gameObjects)
	{
		go->Update(deltaTime);
	}
}

// In this function you can dissassemble GameObjects and add them to various structures, 
// e.g. if the GameObject has a IDrawableComponent component add it to renderLayer structure
void IScene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);

	for (auto component : gameObject->GetAllComponents())
	{
		IDrawableComponent * drawableComponent = dynamic_cast<IDrawableComponent *> (component);

		if (drawableComponent != nullptr)
		{
			_renderLayers[drawableComponent->RenderLayer].push_back(gameObject);
		}
	}
}
