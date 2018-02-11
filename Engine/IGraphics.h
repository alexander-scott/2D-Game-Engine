#pragma once

#include "CustomException.h"
#include "WinDefines.h"
#include "Consts.h"

#include "ISystem.h"
#include "SystemMessageDispatcher.h"

#include "InitaliseGraphicsMessage.h"
#include "DrawSpriteMessage.h"
#include "DrawTextMessage.h"

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

	IGraphics() : ISystem(SystemType::eGraphics) 
	{ 
		SystemMessageDispatcher::Instance().AddListener(this, SystemMessageType::eGraphicsInitalise);
		SystemMessageDispatcher::Instance().AddListener(this, SystemMessageType::eGraphicsStartFrame);
		SystemMessageDispatcher::Instance().AddListener(this, SystemMessageType::eGraphicsEndFrame);
		SystemMessageDispatcher::Instance().AddListener(this, SystemMessageType::eGraphicsDrawSprite);
		SystemMessageDispatcher::Instance().AddListener(this, SystemMessageType::eGraphicsDrawText);
	}

	virtual void RecieveMessage(ISystemMessage& message) override
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

			case SystemMessageType::eGraphicsDrawSprite:
			{
				DrawSpriteMessage & msg = static_cast<DrawSpriteMessage&>(message);
				DrawSprite(msg.Name, msg.Pos, msg.Rect, msg.Rot, msg.Scale, msg.Offset);
			}

			case SystemMessageType::eGraphicsDrawText:
			{
				DrawTextMessage & msg = static_cast<DrawTextMessage&>(message);
				DrawText(msg.Text, msg.Pos, msg.Rot, msg.RgbColours, msg.Scale, msg.Offset);
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
	virtual void DrawText(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset) = 0;

	// Optional overrides //
	virtual void DrawLine(Vec2 v1, Vec2 v2) { }
};