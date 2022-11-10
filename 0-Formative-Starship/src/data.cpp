#include "Data.h"

Data::Data()
{
	_globalFont.loadFromFile("data/arial.ttf");
}

Data& Data::GetInstance()
{
	static Data _instance;
	return _instance;
}
