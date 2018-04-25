#include "GameObject.h"

#include "TransformComponent.h"

GameObject::GameObject(string tag, GUID id) : _tag(tag), _ID(id)
{
	_parent = nullptr;
}

GameObject::~GameObject()
{
	for (auto component : _components)
	{
		if (component != nullptr)
		{
			delete component;
			component = nullptr;
		}
	}

	_components.clear();
}

void GameObject::Start()
{
	for (int i = 0; i < _components.size(); i++)
	{
		// Cast component to IStartableComponent
		IStartableComponent * startable = dynamic_cast<IStartableComponent *> (_components[i]);

		if (startable != nullptr)
		{
			// Is startable
			startable->Start();
		}
	}
}

void GameObject::AddComponent(IComponent * component)
{
	if (component != nullptr)
	{
		component->SetGameObjectID(_ID);
		_components.push_back(component);
	}
}

void GameObject::SendMessageToComponent(IComponentMessage & message)
{
	for (int i = 0; i < _components.size(); i++)
	{
		// Cast component to IMessageableComponent
		IMessageableComponent * messageableComponent = dynamic_cast<IMessageableComponent *> (_components[i]);

		if (messageableComponent != nullptr)
		{
			// Is messageable
			messageableComponent->RecieveMessage(message);
		}
	}
}

void GameObject::SetActive(bool active)
{
	_active = active;
	for (auto component : _components)
	{
		component->SetActive(active);
	}
}

void GameObject::SetParent(shared_ptr<GameObject> parent)
{
	if (_parent != nullptr)
	{
		// Remove THIS GAMEOBJECT as a child from the previous parent
		_parent->RemoveChild(GetSmartPointer());
	}

	_parent = parent; // Set the new parent for THIS GAMEOBJECT
		
	// Set the parent transform in THIS GAMEOBJECT'S transform
	// TODO: Remove this. This is bad. GameObject should not know about TransformComponent
	TransformComponent * transformComponent = GetComponent<TransformComponent>();
	
	if (_parent != nullptr)
	{
		transformComponent->SetParent(_parent->GetComponent<TransformComponent>());
		_parent->AddChild(GetSmartPointer()); // Set THIS GAMEOBJECT as a child for the new parent
	}
	else
	{
		transformComponent->SetParent(nullptr);
	}
}

void GameObject::AddChild(shared_ptr<GameObject> child)
{
	_children.push_back(child);
}

void GameObject::RemoveChild(shared_ptr<GameObject> child)
{
	// Remove a child from THIS GAMEOBJECTS vector of children
	auto it = std::find(_children.begin(), _children.end(), child);
	if (it != _children.end())
		_children.erase(it);
}

shared_ptr<GameObject> GameObject::MakeGameObject(string tag, GUID ID)
{
	return make_shared<GameObject>(tag, ID);
}

shared_ptr<GameObject> GameObject::MakeGameObject(string tag)
{
	GUID gidReference;
	HRESULT hCreateGuid = CoCreateGuid(&gidReference);
	if (FAILED(hCreateGuid))
		throw std::exception("ERROR CREATING GUID FOR GAMEOBJECT");

	return make_shared<GameObject>(tag, gidReference);
}

void GameObject::GetDrawableComponents(map<int, vector<IDrawableComponent*>>& renderLayers)
{
	for (auto component : _components)
	{
		if (component->GetActive())
		{
			// Cast component to IDrawableComponent
			IDrawableComponent * drawableComponent = dynamic_cast<IDrawableComponent *> (component);

			if (drawableComponent != nullptr)
			{
				renderLayers[drawableComponent->RenderLayer].push_back(drawableComponent);
			}
		}
	}
}

void GameObject::Update(float deltaTime)
{
	// Update all updateable components
	for (auto component : _components)
	{
		if (component->GetActive())
		{
			// Cast component to IUpdateableComponent
			IUpdateableComponent * updateableComponent = dynamic_cast<IUpdateableComponent *> (component);

			if (updateableComponent != nullptr)
			{
				// Is updateable
				updateableComponent->Update(deltaTime);
			}
		}
	}
}