#pragma once
#include <string>

class CustomException
{
public:
	CustomException(const wchar_t* file, unsigned int line, const std::wstring& note = L"")
		:
		note(note),
		file(file),
		line(line)
	{}

	const std::wstring& GetNote() const
	{
		return note;
	}

	const std::wstring& GetFile() const
	{
		return file;
	}

	unsigned int GetLine() const
	{
		return line;
	}

	std::wstring GetLocation() const
	{
		return std::wstring(L"Line [") + std::to_wstring(line) + L"] in " + file;
	}

	virtual std::wstring GetFullMessage() const = 0;
	virtual std::wstring GetExceptionType() const = 0;

private:
	std::wstring note;
	std::wstring file;
	unsigned int line;
};