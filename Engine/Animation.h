#pragma once
#include <vector>
#include <map>
#include <d3d11.h>
#include "rapidxml.hpp"
#include <fstream>
#include <iostream>

//Deals with the animations of the sprites. 
//shall load an xml file for each of the sprites 
//in the xml :
//start position, width, height, sequence (ints), type of the sequence (ping pong, "linear", etc.)
//TODO : add sequence tag in animation.xml

using namespace rapidxml;

struct StartPosition {
	int x, y;
};

class Animation
{
public:
	Animation();
	~Animation();
	void AddFrame(RECT rect);
	void GenerateRects();
	void UpdateRect();
	void LoadXml(std::string pathToFile);
	void SetValuesFromXml(int xPos, int yPos, int width, int height, std::string type, std::vector<int> sequence);

private:
	StartPosition _startPosition;
	int _width;
	int _height;
	std::string _type;
	
	RECT _rect;

	std::vector<int> _sequence;
	std::vector<RECT> _rects; 
	std::map<int, std::vector<RECT>(id,)


	

};

