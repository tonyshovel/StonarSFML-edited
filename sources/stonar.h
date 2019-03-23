/***
This file declares global variables and functions which help the program implement better (or maybe worst)


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


#ifndef _stonar_header
#define _stonar_header

/**----Library----**/
#include <iostream>
#include <functional>
#include <vector>
#include <time.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

extern sf::VideoMode screen; ///<The game window size

extern sf::Font gameFont;
extern sf::Font menuFont;

extern sf::Texture background, playerShip, laser, soldierBullet, mouseTexture, explosion, /*Enemy*/ bossShape, soldierShape;
extern sf::Sprite sBackground, sPlayerShip, sLaser, sSoldierBullet, mouseSprite, sExplosion, /*Enemy*/ sBossShape, sSoldierShape;
extern sf::SoundBuffer gunBuffer, gameOverBuffer, explosionBuffer, selectBuffer, destroyedBuffer;
extern sf::Sound gunSound, gameOverSound, explosionSound, selectSound, destroyedSound;

extern float FPS;
extern float TPF;
extern sf::Vector2f scale;

extern std::string playerName;
extern int playerDamage;
extern int currentMoney;
extern int next_Level_Upgrading_Requirement;
/*Global functions*/

void initSpritesAndTextures();
void initFonts();
void initSounds();

void createGame(sf::RenderWindow &window);
void delay(float secs);

void standardHandleEvent(sf::RenderWindow &window);

void loadPlayerInfo_FromFile(std::string path);
void savePlayerInfo_ToFile(std::string path);

#endif // _stonar_header
