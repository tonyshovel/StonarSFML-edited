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

#include "SFML/Graphics.hpp"
#include <windows.h>

using namespace sf;

Color colorList[8] = {Color::Yellow, Color::White, Color::Red, Color::Magenta, Color::Green, Color::Cyan, Color::Blue, Color::Black};

Player::Player()
{
    this->shootCountdown = 0;
    this->healthPoint = 100;
    this->isBlowingUp = 0;
    this->shape = sPlayerShip;
    this->shape.setPosition(int(float(screen.width - spaceShip_width*playerScale)/2), int(float(screen.height)* 4/5));
    this->color = 0;
    this->speed = 530; //Move 500 pixels for each second

    this->centerPoint.setRadius(10*playerScale);
    this->centerPoint.setPosition(76*playerScale + this->shape.getPosition().x, 174*playerScale + this->shape.getPosition().y);
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
    else if (down && (spaceShip_height*playerScale + this->speed*TPF + pos.y) <= screen.height)
        this->shape.move(0, this->speed*TPF);
    else if (left && (pos.x - this->speed*TPF) >= 0)
        this->shape.move(-this->speed*TPF, 0);
    else if (right && (spaceShip_width*playerScale + this->speed*TPF + pos.x) <= screen.width)
        this->shape.move(this->speed*TPF, 0);

    pos = this->shape.getPosition();
    this->centerPoint.setPosition(76*playerScale + pos.x, 174*playerScale + pos.y);
}

void Player::shoot(int shot = 1)
{
    for (int i(shot); i > 0; i--)
    {
        Bullet b;
        b.shape = sLaser;
        b.velocity = {0.0f, -800.0f}; //move 800 per a second
        b.shape.setPosition(centerPoint.getPosition().x, centerPoint.getPosition().y - i*60.0f);
        b.damage = 50;

        this->mainGun.push_back(b);
        gunSound.play();
    }
    this->shootCountdown = 35.0f;
}
