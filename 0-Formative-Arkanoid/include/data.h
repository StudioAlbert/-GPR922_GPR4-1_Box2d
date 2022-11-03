#pragma once
#include <SFML/Graphics/Font.hpp>

// a lot of methods are omitted here
class Data
{
public:
    static Data& GetInstance();
    sf::Font& GlobalFont() { return _globalFont; };

private:
    Data();

    sf::Font _globalFont;

};
