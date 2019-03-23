/***
This file defines global variables such as screen's size or Textures,
which are declared in "stonar.h" and other files.



--------Author--------
Made by: Tony Shovel (Birth year: 2004), Huynh Cong Toai, Vietnamese.

If you can see these comments, that means you have the source code,
My level is just beginner, This game is not designed really well, I hope you guys
can help me to redesign the code to make it cleaner or help me to figure out bugs.


Tony Shovel (Huynh Cong Toai), 13:55 Third of February, 2019
***/


#include "stonar.h"
#include <string>
#include "SFML/Graphics.hpp"

float FPS = 1;
float TPF = 1;

sf::VideoMode screen = sf::VideoMode::getDesktopMode();
sf::Vector2f scale = sf::Vector2f(float(screen.width)/1366, float(screen.height)/768);
sf::Texture background, playerShip, laser, soldierBullet, mouseTexture, bossShape, explosion, soldierShape;
sf::Sprite sBackground, sPlayerShip, sLaser, sSoldierBullet, mouseSprite, sBossShape, sExplosion, sSoldierShape;

void initSpritesAndTextures()
{
    background.loadFromFile("img/background.jpg"); ///1366x768
    sBackground.setTexture(background);
    sBackground.setScale(scale);

	explosion.loadFromFile("img/explosion.png"); ///79x73
	sExplosion.setTexture(explosion);
	sExplosion.setScale(scale);

	soldierShape.loadFromFile("img/darkSoldier_3.png"); ///343x383
	sSoldierShape.setTexture(soldierShape);
	sSoldierShape.scale(0.2*scale.x, 0.2*scale.y);///68.6x76.6

	soldierBullet.loadFromFile("img/fireball.png");///184x182
	sSoldierBullet.setTexture(soldierBullet);
	sSoldierBullet.scale(0.1*scale.x, 0.1*scale.y);///18.4x18.2

	bossShape.loadFromFile("img/boss_2.png"); ///820x969
	sBossShape.setTexture(bossShape);
	sBossShape.scale(0.4*scale.x, 0.4*scale.y);///123x145.35

    playerShip.loadFromFile("img/player.png");///173x291
    sPlayerShip.setTexture(playerShip);
    sPlayerShip.scale(0.3*scale.x, 0.3*scale.y);///51.9x87.3

    laser.loadFromFile("img/laser.png");///90x512
    sLaser.setTexture(laser);
    sLaser.scale(0.1*scale.x, 0.07*scale.y);///9x35x84

    mouseTexture.loadFromFile("img/mouse.png"); ///874x886
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.scale(0.05*scale.x, 0.05*scale.y);
}


sf::Font gameFont;
sf::Font menuFont;

void initFonts()
{
    if (!gameFont.loadFromFile("font/MATURASC.ttf"))
    {
        std::cout << "Cannot read MATURASC font!" << std::endl;
        system("pause");
    }
    if (!menuFont.loadFromFile("font/consola.ttf"))
    {
        std::cout << "Cannot read Consolas font!" << std::endl;
        system("pause");
    }
}

sf::SoundBuffer gunBuffer, gameOverBuffer, explosionBuffer, selectBuffer, destroyedBuffer;
sf::Sound gunSound, gameOverSound, explosionSound, selectSound, destroyedSound;

void initSounds()
{
    destroyedBuffer.loadFromFile("sounds/destroyed.wav");
    destroyedSound.setBuffer(destroyedBuffer);
    destroyedSound.setPlayingOffset(sf::seconds(0.5f));

    gunBuffer.loadFromFile("sounds/laser.wav");
    gunSound.setBuffer(gunBuffer);
    gunSound.setVolume(50.0f);

    gameOverBuffer.loadFromFile("sounds/lost.wav");
    gameOverSound.setBuffer(gameOverBuffer);

    explosionBuffer.loadFromFile("sounds/explosion.wav");
    explosionSound.setBuffer(explosionBuffer);

    selectBuffer.loadFromFile("sounds/select.wav");
    selectSound.setBuffer(selectBuffer);
}

void delay(float secs)
{
    sf::Clock delayClock;
    while (delayClock.getElapsedTime().asSeconds() <= secs);
}
