#pragma once

#include <SFML/Graphics.hpp>

class Box
{
public:
	Box();
	Box(const sf::Vector2f & pos, const sf::Texture& sheets); //creates box
	void draw(sf::RenderWindow& window); //draws the box
	void setPosition(const sf::Vector2f& pos); //sets the position of the box
	sf::Vector2f getPosition(); //returns the position of the box
	void setHeight(float height); //sets the height of the box
	void setWidth(float width); //sets the width of the box
	void setFont(sf::Font &font); //sets the font of the box
	void updateText(std::string text); //updates text of the box
	void setSheets(const sf::Texture &sheets); //sets the sheets used in the box
	void setImgPosition(const sf::IntRect &imgPos); //sets the position of the image in the hseets

private:
	void createShape(); //updates box sprite
	sf::Sprite m_shape; //box sprite
	sf::Texture m_texture; //the sheets
	sf::IntRect m_imgPos; //image position in the sheets

	void createText(); //updates box text
	sf::Text m_text; //box text
	sf::Font m_font; //text font
	sf::Vector2f m_position; //box position
	float m_width; //box width
	float m_height; //box height
	std::string m_string; //text in the box

};
