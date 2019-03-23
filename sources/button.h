#ifndef _button_header
#define _button_header

#include "SFML/Graphics.hpp"

class Button
{
private:
	sf::Sprite _sprite;
	sf::Color _originalColor;
	sf::Color _activatingColor;

	sf::RenderWindow *pWindow;
public:
	Button(sf::Sprite sprite, sf::Color originalColor,
		sf::Vector2f position, sf::RenderWindow *p_window);

    sf::Vector2f getPosition() { return _sprite.getPosition(); }
    sf::FloatRect getGlobalBounds() { return _sprite.getGlobalBounds(); }

	bool isAboutToClick();
	bool isClicked();

	void changeButtonColor();
	void draw();
};

#endif // _button_header
