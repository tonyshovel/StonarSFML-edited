#ifndef _character_header
#define _character_header


#include "bullet.h"
#include "healthbar.h"

class Character
{
protected:
    int healthPoint;
    float shootCountdown;
public:
    int isBlowingUp;
    sf::Sprite shape;
    HealthBar *healthBar;

    Shooter mainGun;
public:
    Character();

    bool canShoot();
    void countDownShoot();

    void takeDamage(int damage);
    bool isDeath() { return (healthPoint > 0 ? false : true); }
    int getHP() { return healthPoint; }

    virtual void move() = 0;
    virtual void shoot(int shot, sf::Color bulletColor) = 0;
};

#endif // _character_header
