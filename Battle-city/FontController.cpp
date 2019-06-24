#include "FontController.h"
#include "Util.h"
#include "Exceptions.h"


FontController::FontController()
	:m_pressStart(std::make_unique<sf::Font>())
{
	if (!m_pressStart->loadFromFile(PRSTARTK))
		throw FileNotOpen();
}

sf::Font * FontController::getPressStartFont()
{
	return m_pressStart.get();
}