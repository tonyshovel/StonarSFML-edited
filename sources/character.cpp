#include "character.h"
#include "stonar.h"

Character::Character()
: healthPoint(0), isBlowingUp(0), shootCountdown(0.0f)
{

}

bool Character::canShoot()
{
    return (shootCountdown <= 0 ? true : false);
}

void Character::countDownShoot()
{
    shootCountdown -= 400*TPF;
}

void Character::takeDamage(int damage)
{
    healthPoint -= damage;
    if (healthPoint < 0)
        healthPoint = 0;

    this->healthBar->makeBar(healthPoint);

    isBlowingUp = 300;
    explosionSound.play();
};
