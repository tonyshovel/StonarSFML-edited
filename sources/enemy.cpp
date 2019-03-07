/***
This file defines the Enemy class and its subclass


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

#include "enemy.h"
#include "stonar.h"

DarkSoldier::DarkSoldier(sf::Vector2f pos = {0.0f, 0.0f})
{
    this->type = darkSoldier;
    this->healthPoint = 500;
    this->velocity = sf::Vector2f(200.0f, 0.0f);
    this->shape = sSoldierShape;

	int lucky = rand() % 2;

	if (!lucky)
		this->velocity = -this->velocity; //move from right to left
    shape.setPosition(pos);
}

void DarkSoldier::move()
{
    this->shape.move(this->velocity*TPF);
    auto pos = this->shape.getPosition();

    if (pos.x <= -10 || pos.x >= screen.width)
    {
        this->velocity = -this->velocity;
        auto ve = this->velocity;

        if (pos.x >= screen.width)
            this->shape.setPosition(pos.x - (abs(ve.x)*TPF)*10, pos.y);
        else
            this->shape.setPosition(pos.x + (abs(ve.x)*TPF), pos.y);
    }
}

void DarkSoldier::shoot(int shot = 1)
{
    for (int i(shot); i > 0; i--)
    {
        Bullet bullet;
        bullet.damage = 20;
        bullet.velocity = { 0.0f, 200.0f };
        bullet.shape = sSoldierBullet;

        auto pos = this->shape.getPosition();
        pos.y = pos.y + i*30.0f;

        bullet.shape.setPosition(pos);
        this->mainGun.push_back(bullet);
    }
    //Gun Sound play
    this->shootCountdown = 700.0f;
}



Boss::Boss(sf::Vector2f pos = { 0.0f, 0.0f })
{
    this->attackCountDown = 100.0f;
    this->type = boss;
    this->healthPoint = 20000;
    this->velocity = { 150.0f, 0.0f };

    if (!(rand() % 2))
        this->velocity = -this->velocity;

    shape = sBossShape;
    shape.setPosition(pos);
}

void Boss::move()
{
    this->shape.move(this->velocity*TPF);
    auto pos = this->shape.getPosition();

    if (pos.x <= -10 || pos.x >= screen.width)
    {
        this->velocity = -this->velocity;
        auto ve = this->velocity;

        if (pos.x  >= screen.width)
            this->shape.setPosition(pos.x - (abs(ve.x)*TPF)*10, pos.y);
        else
            this->shape.setPosition(pos.x + (abs(ve.x)*TPF), pos.y);
    }
}

void Boss::shoot(int shot = 1)
{
    for (int i(shot); i > 0; i--)
    {
        Bullet bullet;
        bullet.damage = 60;
        bullet.velocity = { 0.0f, 160.0f };
        bullet.shape = sSoldierBullet;

        auto pos = this->shape.getPosition();
        pos.x = pos.x + 820*0.15 / 2;
        pos.y = pos.y + 969*0.15 + i*100.0f;

        bullet.shape.setPosition(pos);
        bullet.shape.setColor(sf::Color::Blue);

        this->mainGun.push_back(bullet);
    }
    this->shootCountdown = 700.0f;
}

void Boss::attack(Player &target)
{
    Bullet bullet;
    bullet.damage = 40;
    bullet.shape = sSoldierBullet;
    bullet.shape.setColor(sf::Color::Cyan);

    auto pos = this->shape.getPosition();
    bullet.shape.setPosition(pos.x + 820*0.15 / 2, pos.y + 969*0.15);

    //Flying direction of bullet
    sf::Vector2f aimDir = target.centerPoint.getPosition() - bullet.shape.getPosition();
    sf::Vector2f aimDirNorm = aimDir / float(sqrt((aimDir.x * aimDir.x, aimDir.y * aimDir.y)));
    bullet.velocity = aimDirNorm * 250.0f;

//  Change the bullet flying direction a bit
    float x = float(rand() % 11) / 100;
    float y = float(rand() % 11) / 100;

    int lucky = rand() % 2;

    auto vec = sf::Vector2f(x, y);
    if (lucky % 2)
        vec = -vec;
    bullet.velocity += vec;

    this->mainGun.push_back(bullet);
    this->attackCountDown = 120.0f;
}
