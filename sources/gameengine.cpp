/***
This file define the createGame() function in "stonar.h"


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

#include "stonar.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"

#include "SFML/Graphics.hpp"

#include <cstdlib>
#include <sstream>
#include <typeinfo>

void modifyScore(sf::Text &txt, int score);
void modifyFPS(sf::Text &fpsCounter, int FPS);
void gameOver(sf::RenderWindow &GameWindow);

void standardHandleEvent(sf::RenderWindow &window);

void generateEnemies(Enemies &enemies, sf::Clock &gameClock, int &bossCreated);

float FPS = 1;
float TPF = 1;

void createGame()
{
    sf::Clock gameClock;
    //The score parameter
    sf::Text scoreCounter("SCORE: 0", gameFont, 24);
    scoreCounter.setStyle(sf::Text::Bold);
    scoreCounter.setPosition(screen.width*3/4, 0);

    //The FPS parameter
    sf::Text FPScounter("FPS: 0", menuFont, 22);
    FPScounter.setStyle(sf::Text::Bold);
    FPScounter.setPosition(0, 0);

    sf::Clock fpsClock;
    Enemies enemies;

    Player player;
    float score = 0;
    int level = 0;
    bool isLost = false;
    int bossCreated = 0;
    float EnemyShootCount = 0.0f;
    float modifyFPScount = 0.0f;

    std::cout << "Player's HP: " << player.getHP() << std::endl;

    sf::RenderWindow GameWindow(screen, "STONAR");
    while (GameWindow.isOpen())
    {
        //The whole game
        generateEnemies(enemies, gameClock, bossCreated); //Generate enemies
        standardHandleEvent(GameWindow);
        GameWindow.clear();

        GameWindow.draw(sBackground);
        GameWindow.draw(FPScounter);
        GameWindow.draw(scoreCounter);

        //We check the player here
        {
            GameWindow.draw(player.shape);
            GameWindow.draw(player.centerPoint);

            if (player.isBlowingUp > 0)
            {
                sExplosion.setPosition(player.shape.getPosition());
                GameWindow.draw(sExplosion);
                player.isBlowingUp--;
            }

            player.modifyColor();
            player.move();

            //Shoot action of player
            for (auto it = player.mainGun.begin(); it != player.mainGun.end(); it++)
            {
                GameWindow.draw(it->shape);
                it->shape.move(it->velocity*TPF);

                //Go out of the screen, so we delete the bullet
                if (it->shape.getPosition().y <= 0)
                {
                    player.mainGun.erase(it--);
                    continue;
                }

                //If the bullet hit any enemy, we call e->takeDamge();
                for (auto &e : enemies)
                    if (it->shape.getGlobalBounds().intersects(e->shape.getGlobalBounds()))
                    {
                        e->takeDamage(it->damage);
                        player.mainGun.erase(it--);
                        break;
                    }
            }

            //If press Z and player.canShoot() == true, so we shoot a bullet
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && player.canShoot())
                player.shoot(1);
            else if (!player.canShoot()) //if can't shoot, countDownShoot
                player.countDownShoot();
        }

        //We check enemies here
        {
            for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
            {
                auto e = *enemy;
                if (e->isDeath())
                {
                    float s = (e->type == boss ? 1000 : 50);
                    score += s;

                    delete *enemy;
                    if (enemies.size() > 1)
                        enemies.erase(enemy--);
                    else {
                        enemies.erase(enemy);
                        break;
                    }
                    continue;
                }

                GameWindow.draw(e->shape);
                if (e->isBlowingUp > 0)
                {
                    sExplosion.setPosition(e->shape.getPosition());
                    GameWindow.draw(sExplosion);
                    e->isBlowingUp--;
                }
                e->move();

                if (e->canShoot())
                    e->shoot(e->type == boss ? 1 : 4);
                else
                    e->countDownShoot();
                if (e->canAttackPlayer())
                    e->attack(player);
                else if (e->type == boss)
                    e->countDownAttack();

                for (auto bu = e->mainGun.begin(); bu != e->mainGun.end(); bu++)
                {
                    bu->shape.move(bu->velocity*TPF);

                    auto pos = bu->shape.getPosition();
                    if (pos.x <= 0 || pos.x >= screen.width || pos.y <= 0 || pos.y >= screen.height)
                    {
                        e->mainGun.erase(bu--);
                        continue;
                    }
                    GameWindow.draw(bu->shape);

                    if (bu->shape.getGlobalBounds().intersects(player.centerPoint.getGlobalBounds()))
                    {
                        player.takeDamage(bu->damage);
                        e->mainGun.erase(bu--);
                        std::cout << "Player's HP: " << player.getHP() << std::endl;

                        if (player.isDeath())
                            isLost = true;
                    }
                }
                *enemy = e;
            }
        }

        //Display everything we have drawn
        GameWindow.display();

        //The whole game
        if (isLost)
            gameOver(GameWindow);

        if (int(modifyFPScount) % 400 == 0)
            modifyFPS(FPScounter, FPS);

        modifyScore(scoreCounter, score);

        EnemyShootCount += 400*TPF;
        modifyFPScount += 400*TPF;
        TPF = fpsClock.getElapsedTime().asSeconds();
        FPS = 1.0 / TPF;

        fpsClock.restart();
    }

    //If the programs run these code below, which means the game is over
    bossCreated = 0;
    for (auto it = enemies.begin(); it != enemies.end(); it++)
        delete *it;
    enemies.clear();
}

void modifyScore(sf::Text &txt, int score)
{
    char str[20]; sprintf(str, "SCORE: %d", score);
    txt.setString(str);
}

void modifyFPS(sf::Text &fpsCounter, int FPS)
{
    char str[20]; sprintf(str, "FPS: %d", FPS);
    fpsCounter.setString(str);
}

void gameOver(sf::RenderWindow &GameWindow)
{
    sf::Text gameOver("GAME OVER" , gameFont, 50);
    gameOver.setStyle(sf::Text::Bold);
    gameOver.setPosition(screen.width*1/4, screen.height/2);
    gameOver.setColor(sf::Color::Red);

    GameWindow.draw(gameOver);
    gameOverSound.play();
    GameWindow.display();

    while (GameWindow.isOpen())
    {
        sf::Event e;
        while (!(GameWindow.pollEvent(e) && (e.type == sf::Event::Closed || (e.type == sf::Event::KeyReleased && (e.key.code == sf::Keyboard::Enter || e.key.code == sf::Keyboard::Escape)))));
        GameWindow.close();
    }
}

void generateEnemies(Enemies &enemies, sf::Clock &gameClock, int &bossCreated)
{
//    if (bossCreated > 0)
//    {
//        std::cout << bossCreated << std::endl;
//        for (auto e : enemies)
//            if (e->type == boss)
//            {
//                std::cout << e->shape.getPosition().x << std::endl;
//                std::cout << e->shape.getPosition().y << std::endl;
//            }
//    }
    if (!enemies.size() || (enemies.size() == 1 && enemies.at(0)->type == boss))
    {
        for (int i(0); i < 7; i++)
        {
            int randNum = rand() % 120;
            if (rand() % 2)
                randNum = -randNum;
            sf::Vector2f pos = { screen.width/2 + randNum, screen.height * 1/6 };
            enemies.push_back(new DarkSoldier(pos));
        }
    }

    int secs = gameClock.getElapsedTime().asSeconds();
    if (secs > 0 && secs % 5 == 0 && !bossCreated)
    {
        sf::Vector2f pos = { rand() % 600, 0 };

        enemies.push_back(new Boss(sf::Vector2f(pos)));
        bossCreated++;
    }
}

void standardHandleEvent(sf::RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            break;
        case sf::Event::LostFocus:
            while (!window.pollEvent(event));
            break;
        }
    }
}
