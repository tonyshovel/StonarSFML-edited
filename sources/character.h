#ifndef _character_header
#define _character_header


#include "bullet.h"

class Character
{
protected:
    int healthPoint;
    float shootCountdown;
public:
    int isBlowingUp;
    sf::Sprite shape;

    Shooter mainGun;
public:
    Character();

    bool canShoot();
    void countDownShoot();

    void takeDamage(int damage);
    bool isDeath() { return (healthPoint > 0 ? false : true); }
    int getHP() { return healthPoint; }

    virtual void move() = 0;
    virtual void shoot(int shot) = 0;
};

#endif // _character_header
