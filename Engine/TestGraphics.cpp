#include "TestGraphics.h"

#define GFX_EXCEPTION( hr,note ) TestGraphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

void TestGraphics::Initalise(HWNDKey & key)
{
}

void TestGraphics::Destroy()
{
}

void TestGraphics::EndFrame()
{
}

void TestGraphics::BeginFrame()
{
}

void TestGraphics::PreloadTextures()
{
}

void TestGraphics::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
}

void TestGraphics::DrawText(std::string text, Vec2 pos, float rot, float * rgb, float scale, Vec2 offset)
{
}

void TestGraphics::DrawLine(Vec2 v1, Vec2 v2)
{
}

TestGraphics::Exception::Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line)
	:
	CustomException(file, line, note),
	hr(hr)
{}

std::wstring TestGraphics::Exception::GetFullMessage() const
{
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring(L"Error: ") + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring(L"Description: ") + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring(L"Note: ") + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring(L"Location: ") + location
			: empty);
}

std::wstring TestGraphics::Exception::GetErrorName() const
{
	return L"Graphics Error name";
	//return DXGetErrorString(hr);
}

std::wstring TestGraphics::Exception::GetErrorDescription() const
{
	/*std::array<wchar_t, 512> wideDescription;
	DXGetErrorDescription(hr, wideDescription.data(), wideDescription.size());
	return wideDescription.data();*/
	return L"Graphics Error Description";
}

std::wstring TestGraphics::Exception::GetExceptionType() const
{
	return L"Graphics Exception";
}