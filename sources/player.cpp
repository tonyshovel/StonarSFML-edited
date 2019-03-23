/***
This file defines the Player class


--------Author--------
Made by: Tony Shovel (Birth year: 2004), Huynh Cong Toai, Vietnamese.

If you can see these comments, that means you have the source code,
My level is just beginner, This game is not designed really well, I hope you guys
can help me to redesign the code to make it cleaner or help me to figure out bugs
or you can make somethings base on these codes.


Tony Shovel (Huynh Cong Toai), 13:55 Third of February, 2019

Contact:
    Facebook: https://facebook.com/tony.shovel.90
    Email: hcthuyhcongtoai@gmail.com
           tonyshovel2004@gmail.com
    Phone number: 0918894508
***/

#include "player.h"
#include "bullet.h"
#include "stonar.h"

#include "SFML/Graphics.hpp"
#include <windows.h>

using namespace sf;

Color colorList[8] = {Color::Yellow, Color::White, Color::Red, Color::Magenta, Color::Green, Color::Cyan, Color::Blue, Color::Black};

Player::Player()
{
    this->shootCountdown = 0;
    this->healthPoint = 200;
    this->isBlowingUp = 0;
    this->shape = sPlayerShip;
    this->shape.setPosition((screen.width - this->shape.getGlobalBounds().width)/2, screen.height* 4/5);
    this->color = 0;
    this->speed = 530.0f*(scale.x + scale.y)/2; //Move 500 pixels for each second

    sf::Vector2f hp_pos = sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y + this->shape.getGlobalBounds().height + 10);
    this->healthBar = new HealthBar(this->healthPoint, sf::Vector2f(this->shape.getGlobalBounds().width, 10), sf::Color::Red, hp_pos);

    float spriteScale = this->shape.getGlobalBounds().width/this->shape.getLocalBounds().width;

    this->centerPoint.setRadius(10*spriteScale);
    this->centerPoint.setPosition((this->shape.getGlobalBounds().width - centerPoint.getGlobalBounds().width)/2 + this->shape.getPosition().x,
                                  (this->shape.getGlobalBounds().height/2) + this->shape.getPosition().y);
    this->centerPoint.setFillColor(Color(Color::Yellow));
}

void Player::modifyColor()
{
    this->color = (this->color + 1) % 8;
    this->centerPoint.setFillColor(colorList[this->color]);
}

void Player::move() ///<If player pressed any arrow keys, the spaceship move
{
    int up = Keyboard::isKeyPressed(sf::Keyboard::Up);
    int down = Keyboard::isKeyPressed(sf::Keyboard::Down);
    int left = Keyboard::isKeyPressed(sf::Keyboard::Left);
    int right = Keyboard::isKeyPressed(sf::Keyboard::Right);

    auto pos = this->shape.getPosition();

    if (up && (pos.y - this->speed*TPF) >= 0)
        this->shape.move(0, -this->speed*TPF);
    else if (down && (this->shape.getGlobalBounds().height + this->speed*TPF + pos.y) <= screen.height)
        this->shape.move(0, this->speed*TPF);
    else if (left && (pos.x - this->speed*TPF) >= 0)
        this->shape.move(-this->speed*TPF, 0);
    else if (right && (this->shape.getGlobalBounds().width + this->speed*TPF + pos.x) <= screen.width)
        this->shape.move(this->speed*TPF, 0);

    float spriteScale = this->shape.getGlobalBounds().width/this->shape.getLocalBounds().width;
    this->centerPoint.setPosition((this->shape.getGlobalBounds().width - centerPoint.getGlobalBounds().width)/2 + this->shape.getPosition().x,
                                  (this->shape.getGlobalBounds().height/2) + this->shape.getPosition().y);
    this->healthBar->setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y + this->shape.getGlobalBounds().height + 10));
}

void Player::shoot(int shot = 1, sf::Color bulletColor = sf::Color::White)
{
    for (int i(shot); i > 0; i--)
    {
        Bullet b;
        b.shape = sLaser;
        b.velocity = {0.0f, -800.0f*scale.y}; //move 800 per a second
        b.shape.setPosition(centerPoint.getPosition().x, centerPoint.getPosition().y - i*60.0f);
        b.damage = playerDamage;
        b.shape.setColor(bulletColor);

        this->mainGun.push_back(b);
        gunSound.play();
    }
    this->shootCountdown = 35.0f;
}
