#include "button.h"

//Defintion
Button::Button(sf::Sprite sprite, sf::Color originalColor,
	sf::Vector2f position, sf::RenderWindow *p_window)
{
	this->_sprite = sprite;
	this->_originalColor = originalColor;
	this->_activatingColor = { originalColor.r - 25, originalColor.g - 25, originalColor.b - 25 };
	this->_sprite.setPosition(position);
	this->pWindow = p_window;
}

bool Button::isAboutToClick()
{
	if (this->_sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*this->pWindow))))
		return true;
	return false;
}

bool Button::isClicked()
{
	if (this->isAboutToClick() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void Button::changeButtonColor()
{
	if (this->isAboutToClick())
		this->_sprite.setColor(this->_activatingColor);
	else
		this->_sprite.setColor(this->_originalColor);
}

void Button::draw()
{
    this->pWindow->draw(this->_sprite);
}
