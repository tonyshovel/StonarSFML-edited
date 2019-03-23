/***
This file declares the Enemy class


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

#ifndef _enemy_header
#define _enemy_header

#include "bullet.h"
#include "player.h"
#include "character.h"

enum EnemyType { darkSoldier, boss };

class Enemy : public Character
{
protected:
    float attackCountDown;
    sf::Vector2f velocity;
public:
    EnemyType type;
public:
    Enemy() { this->isBlowingUp = 0; this->shootCountdown = 700.0f; this->attackCountDown = 120.0f; }
    ~Enemy() { destroyedSound.play(); }

    bool canAttackPlayer() { return (this->attackCountDown <= 0 ? true : false); }
    void countDownAttack() { this->attackCountDown -= 400*TPF; }

    virtual void attack(Player &target) = 0;
};

class DarkSoldier : public Enemy
{
public:
    void move();
    void shoot(int shot, sf::Color bulletColor);

    bool canAttackPlayer() { return false; }
    void attack(Player &target) {};

	DarkSoldier(sf::Vector2f pos, sf::Sprite sprite, sf::Vector2f newVelocity, int HP);
};

class Boss : public Enemy
{
public:
    void move();
    void shoot(int shot, sf::Color bulletColor);

    bool canAttackPlayer();
    void attack(Player &target);

    Boss(sf::Vector2f pos, sf::Sprite sprite, sf::Vector2f newVelocity, int HP);
};

typedef std::vector<Enemy*> Enemies;

#endif // _enemy_header
