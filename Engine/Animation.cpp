#include "Animation.h"



Animation::Animation()
{
}

Animation::Animation(std::string path)
{
	LoadXml(path);
}


Animation::~Animation()
{
}

void Animation::AddFrame(RECT rect)
{
	_rects.push_back(rect); //TODO : delete or use & change 
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

void Animation::UpdateRect(float dt)
{
	//float fakeTimer = 150.0f;//TODO : use REAL time value. But should use system's time..?
	//float t = 0.0f;
	//while (t < fakeTimer)
	////while( currentTime + dt >= holdTime ){ //add time element IN animation? Or retrieve it from engine?
	//{
		AdvanceRect();
	//	t += 0.001f;
	//	//currentTime -= holdTime;
	//}
	////}

}

void Animation::AdvanceRect()
{
	//find which rect of the map _rect is
	//then retrieve the iterator of the sequence
	//then change the rect according to the next sequence id 
	//don't forget the "modulo" (french term, idk which one it is in english)

	if (_iterator < _sequence.size()) {
		int id = _sequence.at(_iterator);
		std::map<int, RECT*>::iterator it = _idRect.find(_sequence.at(_iterator));

		if (it != _idRect.end()) {
			_rect = it->second;
		}
		_iterator++;
	}
	else {
		_iterator = 0;
	}
}

void Animation::LoadXml2(std::string pathToFile)
{
	xml_document<> doc;
	xml_node<>* node;
	//xml_node<>*nodeAnimation;
	xml_node<>* nodePos;
	xml_node<>* nodeDim;
	xml_node<>* nodeSequence;
	xml_node<>* nodeRect;

	//std::ifstream file("..\\Resources\\Animations\\animation.xml");
	std::ifstream file(pathToFile);
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');


	doc.parse<0>(&buffer[0]);
	

	//retrieve root node
	node = doc.first_node("Anims");
	for (xml_node<>*nodeAnimation = node->first_node("Animation"); nodeAnimation; nodeAnimation = nodeAnimation->next_sibling()) {

	
		//float xPos = (float)atof(_node->first_attribute("xpos")->value());
		nodePos = nodeAnimation->first_node("StartPosition");

		int xPos = (int)atof(nodePos->first_attribute("xpos")->value());
		int yPos = (int)atof(nodePos->first_attribute("ypos")->value());


		nodeDim = nodeAnimation->first_node("Dimensions");

		int width = (int)atof(nodeDim->first_attribute("width")->value());
		int height = (int)atof(nodeDim->first_attribute("height")->value());

		std::string type = nodeAnimation->first_node("Type")->first_attribute("name")->value();

		//dealing with the sequence
		nodeSequence = nodeAnimation->first_node("Sequence");
		std::vector<int> sequence;

		for (xml_attribute<>* attribute = nodeSequence->first_attribute("seq"); attribute; attribute = attribute->next_attribute()) {
			sequence.push_back((int)atof(attribute->value()));
		}

		//deal with the rectangles now...
		std::map<int, RECT*> idRect;
		nodeRect = nodeAnimation->first_node("Rectangles");

		for (xml_node<>* rect = nodeRect->first_node("Rect"); rect; rect = rect->next_sibling()) {
			RECT *r = new RECT();
			r->top = (int)atof(rect->first_attribute("top")->value());
			r->bottom = (int)atof(rect->first_attribute("bottom")->value());
			r->right = (int)atof(rect->first_attribute("right")->value());
			r->left = (int)atof(rect->first_attribute("left")->value());
			int id = (int)atof(rect->first_attribute("id")->value());
			idRect[id]= r;
		}
	SetValuesFromXml(xPos, yPos, width, height, type, sequence, idRect);
	//create animation with those values. Add them to the map with the type of the anim as string key
	Animation anim = CreateAnimationFromXml(xPos, yPos, width, height, type, sequence, idRect);
	_nameAnimations[type] = anim;
	}
}

void Animation::LoadXml(std::string pathToFile)
{
	xml_document<> doc;
	xml_node<>* node;
	//xml_node<>*nodeAnimation;
	xml_node<>* nodePos;
	xml_node<>* nodeDim;
	xml_node<>* nodeSequence;
	xml_node<>* nodeRect;

	//std::ifstream file("..\\Resources\\Animations\\animation.xml");
	std::ifstream file(pathToFile);
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	


	try {
		doc.parse<0>(&buffer[0]);
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Runtime error was: " << e.what() << std::endl;
	}
	catch (const rapidxml::parse_error& e)
	{
		std::string er = e.what();
			std::cerr << "Parse error was: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error was: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "An unknown error occurred." << std::endl;
	}

	//retrieve root node
	node = doc.first_node("Animation");

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
		std::map<int, RECT*> idRect;
		nodeRect = node->first_node("Rectangles");

		for (xml_node<>* rect = nodeRect->first_node("Rect"); rect; rect = rect->next_sibling()) {
			RECT *r = new RECT();
			r->top = (int)atof(rect->first_attribute("top")->value());
			r->bottom = (int)atof(rect->first_attribute("bottom")->value());
			r->right = (int)atof(rect->first_attribute("right")->value());
			r->left = (int)atof(rect->first_attribute("left")->value());
			int id = (int)atof(rect->first_attribute("id")->value());
			idRect[id] = r;
		}
		SetValuesFromXml(xPos, yPos, width, height, type, sequence, idRect);
		//create animation with those values. Add them to the map with the type of the anim as string key
		//Animation anim = CreateAnimationFromXml(xPos, yPos, width, height, type, sequence, idRect);
		//_nameAnimations[type] = anim;

}

void Animation::SetValuesFromXml(int xStartPos, int yStartPos, int width, int height, std::string type, std::vector<int> sequence, std::map<int, RECT*> idRect)
{
	_startPosition.x = xStartPos;
	_startPosition.y = yStartPos;
	_width = width;
	_height = height;
	_type = type;

	RECT *startRect = new RECT(); //first rect of the sequence

	startRect->left = _startPosition.x;
	startRect->right = _startPosition.x + _width;
	startRect->top = _startPosition.y;
	startRect->bottom = _startPosition.y + _height;
	_rect = startRect;

	_sequence = sequence;
	_idRect = idRect;
}

RECT* Animation::GetRect()
{
	return _rect;
}

std::string Animation::GetType()
{
	return _type;
}

Animation Animation::CreateAnimationFromXml(int xPos, int yPos, int width, int height, std::string type, std::vector<int> sequence, std::map<int, RECT*> idRect)
{
	Animation anim;
	//anim._startPosition.x = xStartPos;
	//anim._startPosition.y = yStartPos;
	anim._width = width;
	anim._height = height;
	anim._type = type;

	RECT *startRect = new RECT(); //first rect of the sequence

	startRect->left = _startPosition.x;
	startRect->right = _startPosition.x + _width;
	startRect->top = _startPosition.y;
	startRect->bottom = _startPosition.y + _height;
	anim._rect = startRect;

	anim._sequence = sequence;
	anim._idRect = idRect;
	return anim;
}

Animation Animation::RetrieveAnimationFromType(std::string type)
{
	std::map<std::string, Animation>::iterator it = _nameAnimations.find(type);
	if (it != _nameAnimations.end())
		return it->second;
	else return Animation(); //would make it break ...
}

