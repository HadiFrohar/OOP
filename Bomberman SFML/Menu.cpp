#include "Menu.h"
#include "Utilities.h"




Menu::Menu(Board &board)
	:m_board(board), m_paused(false)
{
	if (!m_logo.loadFromFile(LOGOPATH))
		loadCrash();

	if (!m_font.loadFromFile(SEGAFONT))
		loadCrash();

	createBorder();
	createTexts();
	createImages();

}

void Menu::display()
{
	m_showWindow = true;

	m_buttonId = 0;
	m_texts[m_buttonId].setFillColor(sf::Color::Red);
	m_board.adjustSize(WINDOWSIZE, true);
	while (m_board.isOn() && m_showWindow)
	{
		m_board.clear();
		for (size_t i = 0; i < m_walls.size(); i++)
			m_walls[i].draw(m_board.getWindow());

		for (size_t i = 0; i < m_texts.size(); i++)
			m_board.getWindow().draw(m_texts[i]);

		for (size_t i = 0; i < m_images.size(); i++)
			m_board.getWindow().draw(m_images[i]);

		m_board.getWindow().draw(m_status);

		m_board.getWindow().display();
		HandleEvents(m_board.getWindow());
	}

}

void Menu::createImages()
{
	m_images.push_back(createImg(m_logo, { 100, 100 }));
	m_images.push_back(createImg(m_board.getSheets(), { WINDOWSIZE - 200, WINDOWSIZE / 2 + 150 }));
	m_images[1].setTextureRect(sf::IntRect(FOURTH + 12, EIGHTH, OBJECTIMGSIZE-12, OBJECTIMGSIZE));
	m_images[1].setScale(2.0f, 2.0f);
	m_images.push_back(createImg(m_board.getSheets(), { WINDOWSIZE - 220, WINDOWSIZE / 2 +144}));
	m_images[2].setTextureRect(sf::IntRect(FIRST, NINETH, OBJECTIMGSIZE, OBJECTIMGSIZE));

	m_iconTexture.loadFromImage(m_board.getIcon());
	m_images.push_back(createImg(m_iconTexture, { OBJECTSIZE * 2, WINDOWSIZE - OBJECTSIZE * 4 }));
	m_images[3].setScale(0.5f, 0.5f);
}


void Menu::createBorder()
{

	for (int i = 0; i < WINDOWSIZE; i += OBJECTSIZE)
	{
		m_walls.push_back(Wall({(float) i, 0 }, m_board.getSheets()));
		m_walls.push_back(Wall({ (float)i, WINDOWSIZE - OBJECTSIZE }, m_board.getSheets()));
	}

	for (int i = 0; i < WINDOWSIZE; i += OBJECTSIZE)
	{
		m_walls.push_back(Wall({ 0, (float)i }, m_board.getSheets()));
		m_walls.push_back(Wall({ WINDOWSIZE - OBJECTSIZE , (float)i }, m_board.getSheets()));
	}

}


void Menu::createTexts()
{
	m_texts.push_back(createText("START"));
	m_texts.push_back(createText("EXIT"));
	m_status = createText("");
	m_status.setCharacterSize(FONTSIZE * 3);
	m_status.setFont(m_board.getFont());


}

void Menu::pause()
{
	m_texts[0].setString("CONTINUE");
	m_texts[0].setOrigin(m_texts[0].getLocalBounds().width / 2.0f, m_texts[0].getLocalBounds().height / 2.0f);
	m_paused = true;
	display();
	m_paused = false;
}

void Menu::playAgain()
{
	m_texts[0].setString("PLAY AGAIN");
	m_texts[0].setOrigin(m_texts[0].getLocalBounds().width / 2.0f, m_texts[0].getLocalBounds().height / 2.0f);
	display();
}

void Menu::updateStatus(std::string text)
{
	m_status.setString(text);
	m_status.setOrigin(m_status.getLocalBounds().width / 2.0f, m_status.getLocalBounds().height / 2.0f);
}



sf::Text Menu::createText(std::string str) const
{
	sf::Text text;
	text.setPosition({ WINDOWSIZE / 2, WINDOWSIZE / 2 + (float) m_texts.size() * 100 });
	text.setString(str);
	text.setCharacterSize(FONTSIZE*5);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3);
	text.setFont(m_font);
	text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
	return text;
}

sf::Sprite Menu::createImg(sf::Texture &texture, sf::Vector2f pos) const
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	return sprite;
}

void Menu::HandleEvents(sf::RenderWindow &window)
{
	sf::Event event;
	if (window.waitEvent(event))
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			exit(EXIT_SUCCESS);
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Enter)
			{
				if (m_buttonId == 1)
					window.close();

				m_showWindow = false;
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				m_texts[m_buttonId].setFillColor(sf::Color::White);
				if (m_buttonId == m_texts.size() - 1)
					m_buttonId = 0;
				else
					m_buttonId++;
				m_texts[m_buttonId].setFillColor(sf::Color::Red);

			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				m_texts[m_buttonId].setFillColor(sf::Color::White);
				if (m_buttonId == 0)
					m_buttonId = (int)m_texts.size() - 1;
				else
					m_buttonId--;
				m_texts[m_buttonId].setFillColor(sf::Color::Red);
			}
			else if (event.key.code == sf::Keyboard::Escape)
				if (m_paused)
				{
					m_showWindow = false;
					break;
				}
		}
}
