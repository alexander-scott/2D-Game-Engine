#pragma once

#include "CustomException.h"
#include "Consts.h"

#include "ISystem.h"

#include "InitaliseGraphicsMessage.h"
#include "DrawSceneMessage.h"

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
				
				// Draw all sprites
				auto spritesToDraw = msg.GetSpriteData();
				for (int i = 0; i < spritesToDraw.size(); i++)
				{
					DrawSprite(spritesToDraw[i].Name, 
						spritesToDraw[i].Pos, 
						spritesToDraw[i].Rect, 
						spritesToDraw[i].Rot, 
						spritesToDraw[i].Scale, 
						spritesToDraw[i].Offset);
				}

				// Draw all text
				auto textToDraw = msg.GetTextData();
				for (int i = 0; i < textToDraw.size(); i++)
				{
					DrawText2D(textToDraw[i].Text,
						textToDraw[i].Pos,
						textToDraw[i].Rot,
						textToDraw[i].RgbColours,
						textToDraw[i].Scale, 
						textToDraw[i].Offset);
				}
				break;
			}
		}
	}

protected:
	// Mandatory overrides //
	virtual void Initalise(class HWNDKey& key) = 0;
	virtual void Destroy() = 0;

	virtual void EndFrame() = 0;
	virtual void BeginFrame() = 0;

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) = 0;
	virtual void DrawText2D(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset) = 0;

	// Optional overrides //
	virtual void DrawLine(Vec2 v1, Vec2 v2) { }
};