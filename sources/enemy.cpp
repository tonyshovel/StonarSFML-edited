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

DarkSoldier::DarkSoldier(sf::Vector2f pos = {0.0f, 0.0f},
                         sf::Sprite sprite = sSoldierShape,
                         sf::Vector2f newVelocity = { 0.0f, 0.0f},
                         int HP = 500)
{
    this->type = darkSoldier;
    this->velocity = newVelocity;
    this->shape = sprite;
    this->healthPoint = HP;

    sf::Vector2f hp_pos = sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y + this->shape.getGlobalBounds().height + 10);
    this->healthBar = new HealthBar(this->healthPoint, sf::Vector2f(this->shape.getGlobalBounds().width, 10), sf::Color::Yellow, hp_pos);

	int lucky = rand() % 2;

	if (!lucky)
		this->velocity = -this->velocity; //move from right to left
    shape.setPosition(pos);
}

void DarkSoldier::move()
{
    this->shape.move(this->velocity*TPF);
    auto pos = this->shape.getPosition();

    if (pos.x <= -10 || pos.x >= screen.width || pos.y <= -10 || pos.y >= screen.height)
    {
        this->velocity = -this->velocity;
        this->shape.move(this->velocity*TPF);
    }
    this->healthBar->setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y + this->shape.getGlobalBounds().height + 10));
}

void DarkSoldier::shoot(int shot = 1, sf::Color bulletColor = sf::Color::White)
{
    for (int i(shot); i > 0; i--)
    {
        Bullet bullet;
        bullet.damage = 20;
        bullet.velocity = { 0.0f, 200.0f*scale.y };
        bullet.shape = sSoldierBullet;
        bullet.shape.setColor(bulletColor);

        sf::Vector2f pos = { this->shape.getPosition().x + (this->shape.getGlobalBounds().width - bullet.shape.getGlobalBounds().width)/2,
                             this->shape.getPosition().y + this->shape.getGlobalBounds().height};
        pos.y = pos.y + i*30.0f*scale.y;

        bullet.shape.setPosition(pos);
        this->mainGun.push_back(bullet);
    }
    //Gun Sound play
    this->shootCountdown = 700.0f;
}



Boss::Boss(sf::Vector2f pos = {0.0f, 0.0f},
                         sf::Sprite sprite = sBossShape,
                         sf::Vector2f newVelocity = { 0.0f, 0.0f},
                         int HP = 20000)
{
    this->type = boss;
    /*
    this->shape = sprite;
    this->healthPoint = HP;
    this->velocity = newVelocity;*/
    this->shape = sBossShape;
    this->healthPoint = 20000;
    this->velocity = { 150.0f*scale.x, 0.0f };

    if (!(rand() % 2))
        this->velocity = -this->velocity;

    shape = sBossShape;
    shape.setPosition(pos);

    sf::Vector2f hp_pos = sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y + this->shape.getGlobalBounds().height + 10);
    this->healthBar = new HealthBar(this->healthPoint, sf::Vector2f(this->shape.getGlobalBounds().width, 15), sf::Color::Magenta, hp_pos);
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
    this->healthBar->setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y + this->shape.getGlobalBounds().height + 10));
}

void Boss::shoot(int shot = 1, sf::Color bulletColor = sf::Color::White)
{
    for (int i(shot); i > 0; i--)
    {
        Bullet bullet;
        bullet.damage = 60;
        bullet.velocity = { 0.0f, 160.0f*(scale.x + scale.y)/2 };
        bullet.shape = sSoldierBullet;
        bullet.shape.setColor(bulletColor);

        sf::Vector2f pos = { this->shape.getPosition().x + (this->shape.getGlobalBounds().width - bullet.shape.getGlobalBounds().width)/2,
                             this->shape.getPosition().y + (this->shape.getGlobalBounds().height - bullet.shape.getGlobalBounds().height)/2 };

        bullet.shape.setPosition(pos);
        bullet.shape.setColor(sf::Color::Magenta);

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

    sf::Vector2f pos = { this->shape.getPosition().x + (this->shape.getGlobalBounds().width - bullet.shape.getGlobalBounds().width)/2,
                         this->shape.getPosition().y + (this->shape.getGlobalBounds().height - bullet.shape.getGlobalBounds().height)/2 };
    bullet.shape.setPosition(pos);

    //Flying direction of bullet
    sf::Vector2f aimDir = target.centerPoint.getPosition() - bullet.shape.getPosition();
    sf::Vector2f aimDirNorm = aimDir / float(sqrt((aimDir.x * aimDir.x, aimDir.y * aimDir.y)));
    bullet.velocity = aimDirNorm * (250.0f * (scale.x + scale.y)/2);

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
