#pragma once

#include "Consts.h"

#include "IComponent.h"
#include "IUpdateableComponent.h"
#include "IDrawableComponent.h"
#include "IMessageableComponent.h"

#include "DrawSceneMessage.h"

#include <objbase.h>

using namespace std;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject(string tag, GUID id);
	~GameObject();

	virtual void Draw(DrawSceneMessage& message);
	virtual void Update(float deltaTime);

	void AddComponent(IComponent* component);

	vector<IComponent*> GetAllComponents() { return _components; }
	void SendMessageToComponent(IComponentMessage& message);

	void SetActive(bool active);
	bool GetActive() { return _active; }

	GUID GetID() { return _ID; }
	string GetTag() { return _tag; }

	void SetParent(shared_ptr<GameObject> parent);
	shared_ptr<GameObject> GetParent() { return _parent; }

	void AddChild(shared_ptr<GameObject> child);
	void RemoveChild(shared_ptr<GameObject> child);
	vector<shared_ptr<GameObject>> GetChildren() { return _children; }

	template<class T>
	T * GetComponent()
	{
		for (auto component : _components)
		{
			T* tComponent = dynamic_cast<T *> (component);

			if (tComponent != nullptr)
			{
				return tComponent;
			}
		}

		return nullptr;
	}

	template<class T>
	vector<T*> GetComponents()
	{
		vector<T*> components;
		for (auto component : _components)
		{
			T* tComponent = dynamic_cast<T *> (component);

			if (tComponent != nullptr)
			{
				components.push_back(tComponent);
			}
		}

		return components;
	}

	template<class T>
	void RemoveComponent()
	{
		for (int i = 0; i < _components.size(); i++)
		{
			T* tComponent = dynamic_cast<T *> (_components[i]);

			if (tComponent != nullptr)
			{
				_components.erase(_components.begin() + i);
				delete tComponent;
				return;
			}
		}
	}

	std::shared_ptr<GameObject> GetSmartPointer()
	{
		return shared_from_this();
	}

	static shared_ptr<GameObject> MakeGameObject(string tag, GUID ID);
	static shared_ptr<GameObject> MakeGameObject(string tag);

protected:
	vector<IComponent*>				_components;
	shared_ptr<GameObject>			_parent;
	vector<shared_ptr<GameObject>>	_children;

	bool							_active;
	string							_tag;
	GUID							_ID;
};
