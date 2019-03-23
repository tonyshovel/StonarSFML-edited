#ifndef _healthbar_header
#define _healthbar_header

#include "SFML/Graphics.hpp"

class HealthBar
{
private:
	sf::RectangleShape blankBar;
	sf::RectangleShape healthBar;

	int maxHP;
	float maxLength;
    sf::Vector2f HealthBar_DefaultPosition;
public:
	HealthBar(int max_HP, sf::Vector2f size, sf::Color color, sf::Vector2f position);

	//getter and setter
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f position);

	sf::Vector2f getSize();
	sf::Vector2f getPosition();

	//core
	void makeBar(int remainingHP);
	void draw(sf::RenderWindow &window);
};

#endif // _healthbar_header
