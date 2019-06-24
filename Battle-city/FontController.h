#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
class FontController
{
public:
	FontController(); //loads fonts
	sf::Font *getPressStartFont(); //retunrs ps font

private:
	std::unique_ptr<sf::Font> m_pressStart;
};

