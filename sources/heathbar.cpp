#include "healthbar.h"

#include "SFML/Graphics.hpp"


///Constructor
HealthBar::HealthBar(int max_HP, sf::Vector2f size, sf::Color color, sf::Vector2f position)
{
    this->maxLength = size.x;
    this->setSize(size);
    this->healthBar.setFillColor(color);
    this->maxHP = max_HP;
    this->makeBar(max_HP);

    this->blankBar.setPosition(position);

    auto rectBlankBar = blankBar.getGlobalBounds();
    auto rectHealthBar = healthBar.getGlobalBounds();

    this->HealthBar_DefaultPosition = { (rectBlankBar.width - rectHealthBar.width)/2,
                                        (rectBlankBar.height - rectHealthBar.height)/2 };

    sf::Vector2f healthBarPosition = { this->HealthBar_DefaultPosition + this->blankBar.getPosition() };
    this->healthBar.setPosition(healthBarPosition);

}

///Core
void HealthBar::makeBar(int remainingHP)
{
    float percentages = float(remainingHP)/maxHP;
    auto updateSize = this->healthBar.getSize();

    updateSize.x = percentages*this->maxLength;
    this->healthBar.setSize(updateSize);
}

void HealthBar::draw(sf::RenderWindow &window)
{
    window.draw(this->blankBar);
    window.draw(this->healthBar);
}

///Getter and Setter
sf::Vector2f HealthBar::getPosition() { return this->blankBar.getPosition(); }
sf::Vector2f HealthBar::getSize() { return this->blankBar.getSize(); }

void HealthBar::setPosition(sf::Vector2f position)
{
    this->blankBar.setPosition(position);
    this->healthBar.setPosition(this->HealthBar_DefaultPosition + this->blankBar.getPosition());
}

void HealthBar::setSize(sf::Vector2f size)
{
    this->blankBar.setSize(size);
    this->healthBar.setSize(size*0.8f);
}

