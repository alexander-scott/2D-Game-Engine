#include "GameObject.h"

GameObject::GameObject(string tag, int id)
{
	_parent = nullptr;
}

GameObject::~GameObject()
{
	for (auto component : _components)
	{
		delete component;
		component = nullptr;
	}
}

void GameObject::AddComponent(IComponent * component)
{
	if (component != nullptr)
	{
		_components.push_back(component);
	}
}

void GameObject::SendMessageToComponent(IComponentMessage & message)
{
	for (int i = 0; i < _components.size(); i++)
	{
		if (_components[i]->GetType() == message.ComponentRecipient)
		{
			// Cast component to IMessageable
			IMessageable * messageableComponent = dynamic_cast<IMessageable *> (_components[i]);

			if (messageableComponent != nullptr)
			{
				// Is messageable
				messageableComponent->RecieveMessage(message);
			}
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
		_parent->RemoveChild(shared_ptr<GameObject>(this));
	}

	_parent = parent; // Set the new parent for THIS GAMEOBJECT

	// Set the parent transform in THIS GAMEOBJECT'S transform
	for (auto component : _components)
	{
		// Cast component to TransformComponent
		TransformComponent * transformComponent = dynamic_cast<TransformComponent *> (component);
		if (transformComponent != nullptr)
		{
			transformComponent->SetParent(_parent->GetComponent<TransformComponent>());
			break;
		}
	}

	if (_parent != nullptr)
	{
		_parent->AddChild(shared_ptr<GameObject>(this)); // Set THIS GAMEOBJECT as a child for the new parent
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

shared_ptr<GameObject> GameObject::MakeGameObject(string tag, int ID)
{
	auto gameObject = make_shared<GameObject>(tag, ID);
	return gameObject;
}

void GameObject::Draw()
{
	for (auto component : _components)
	{
		if (component->GetActive())
		{
			// Cast component to IDrawable
			IDrawable * drawableComponent = dynamic_cast<IDrawable *> (component);

			if (drawableComponent != nullptr)
			{
				// Is drawable
				drawableComponent->Draw();
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
			// Cast component to IUpdateable - This is bad!!
			IUpdateable * updateableComponent = dynamic_cast<IUpdateable *> (component);

			if (updateableComponent != nullptr)
			{
				// Is updateable
				updateableComponent->Update(deltaTime);
			}
		}
	}
}