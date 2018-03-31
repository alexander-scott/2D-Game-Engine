#pragma once
#include <vector>
#include <map>
#include <d3d11.h>
//#define RAPIDXML_NO_EXCEPTIONS 
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
	Animation(std::string path);
	~Animation();
	void AddFrame(RECT rect);
	void GenerateRects(); //TODO : delete
	void UpdateRect(float dt);
	void AdvanceRect();
	void LoadXml(std::string pathToFile);
	void LoadXml2(std::string pathToFile);
	void SetValuesFromXml(int xPos, int yPos, int width, int height, std::string type, std::vector<int> sequence, std::map<int, RECT*> idRect);

	RECT* GetRect();
	std::string GetType();

	Animation CreateAnimationFromXml(int xPos, int yPos, int width, int height, std::string type, std::vector<int> sequence, std::map<int, RECT*> idRect);
	Animation RetrieveAnimationFromType(std::string type); //returns corresponding animation from _nameAnimation

private:
	int _iterator = 0;
	StartPosition _startPosition;
	int _width;
	int _height;
	std::string _type; //ex : ping pong, linear... Not used yet now but should be
	
	RECT *_rect = nullptr; //actual rect to display

	std::vector<int> _sequence; //sequence of the ids of the rectangles we want to display for the animation
	std::vector<RECT> _rects;  //not really useful anymore...?
	std::map<int, RECT*>_idRect;
	std::map<std::string, Animation>_nameAnimations;

	

};

