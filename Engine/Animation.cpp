#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::AddFrame(RECT rect)
{
	_rects.push_back(rect);
}

void Animation::GenerateRects()
{
	//remplit le vecteur de rects en fonction de la sequence d'animations
	//(fills the rects vector according to the animation sequence)
	/*assert(_sequence.size() >= 1);
	for (int i = 0; i < _sequence.size(); i++) {
		RECT r;
		r.top = 
	}*/

}

void Animation::LoadXml(std::string pathToFile)
{
	xml_document<> doc;
	xml_node<>* node;
	xml_node<>* nodePos;
	xml_node<>* nodeDim;
	xml_node<>* nodeSequence;
	xml_node<>* nodeRect;

	std::ifstream file("..\\Resources\\Animations\\animation.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	//retrieve root node
	node = doc.first_node("Animation");
	//float xPos = (float)atof(_node->first_attribute("xpos")->value());
	nodePos = node->first_node("StartPosition");

	int xPos = (int)atof(nodePos->first_attribute("xpos")->value());
	int yPos = (int)atof(nodePos->first_attribute("ypos")->value());


	nodeDim = node->first_node("Dimensions");

	int width = (int)atof(nodeDim->first_attribute("width")->value());
	int height = (int)atof(nodeDim->first_attribute("height")->value());

	std::string type = node->first_node("Type")->first_attribute("name")->value();

	//dealing with the sequence
	nodeSequence = node->first_node("Sequence");
	std::vector<int> sequence;

	for (xml_attribute<>* attribute = nodeSequence->first_attribute("seq"); attribute; attribute = attribute->next_attribute()) {
		sequence.push_back((int)atof(attribute->value()));
	}

	//deal with the rectangles now...
	nodeDim = node->first_node("Rectangles");
	//TODO


	SetValuesFromXml(xPos, yPos, width, height, type, sequence);
}

void Animation::SetValuesFromXml(int xStartPos, int yStartPos, int width, int height, std::string type, std::vector<int> sequence)
{
	_startPosition.x = xStartPos;
	_startPosition.y = yStartPos;
	_width = width;
	_height = height;
	_type = type;

	RECT startRect;

	startRect.left = _startPosition.x;
	startRect.right = _startPosition.x + _width;
	startRect.top = _startPosition.y;
	startRect.bottom = _startPosition.y + _height; 
	_rect = startRect;

	_sequence = sequence;
}

