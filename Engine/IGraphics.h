#pragma once

#include "CustomException.h"
#include "Consts.h"

#include "ISystem.h"

#include "InitaliseGraphicsMessage.h"
#include "DrawSceneMessage.h"

#include "Scene.h"

#include <wrl.h>

class IGraphics : public ISystem
{
public:
	class Exception : public CustomException
	{
		public:
			Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line);
			std::wstring GetErrorName() const;
			std::wstring GetErrorDescription() const;
			virtual std::wstring GetFullMessage() const override;
			virtual std::wstring GetExceptionType() const override;

		private:
			HRESULT hr;
	};

	IGraphics(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
		: ISystem(SystemType::eGraphics, dispatcher) { }
	
	IGraphics(std::shared_ptr<SystemMessageDispatcher> dispatcher, HWNDKey &key)
		: ISystem(SystemType::eGraphics, dispatcher) { }


	void InitaliseListeners() override
	{
		SubscribeToMessageType(SystemMessageType::eGraphicsInitalise);
		SubscribeToMessageType(SystemMessageType::eGraphicsStartFrame);
		SubscribeToMessageType(SystemMessageType::eGraphicsEndFrame);
		SubscribeToMessageType(SystemMessageType::eGraphicsDrawScene);
	}

	void RecieveMessage(ISystemMessage& message) override
	{
		switch (message.Type)
		{
			case SystemMessageType::eGraphicsInitalise:
			{
				InitaliseGraphicsMessage & msg = static_cast<InitaliseGraphicsMessage&>(message);
				Initalise(msg.Key);
				break;
			}

			case SystemMessageType::eGraphicsDestroy:
			{
				Destroy();
				break;
			}
				
			case SystemMessageType::eGraphicsStartFrame:
			{
				BeginFrame();
				break;
			}
				
			case SystemMessageType::eGraphicsEndFrame:
			{
				EndFrame();
				break;
			}	

			case SystemMessageType::eGraphicsDrawScene:
			{
				DrawSceneMessage & msg = static_cast<DrawSceneMessage&>(message);
				auto gameObjects = msg.GetScene()->GetAllGameObjects();

				// Create render layers
				map<int, vector<IDrawableComponent*>> renderLayers;
				for (auto go : gameObjects)
				{
					go->GetDrawableComponents(renderLayers);
				}

				// Draw render layers in order
				map<int, vector<IDrawableComponent*>>::iterator renderLayer;
				for (renderLayer = renderLayers.begin(); renderLayer != renderLayers.end(); renderLayer++)
				{
					for (int i = 0; i < renderLayer->second.size(); i++)
					{
						DrawComponent(renderLayer->second[i]);
					}
				}

				break;
			}
		}
	}

protected:
	virtual void Initalise(class HWNDKey& key) = 0;
	virtual void Destroy() = 0;

	virtual void EndFrame() = 0;
	virtual void BeginFrame() = 0;

	virtual void DrawComponent(IDrawableComponent* component) = 0;
};