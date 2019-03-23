/***
This file contain the main function


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
#include "menu.h"
#include "upgrade.h"
#include "SFML/Graphics.hpp"

int main()
{
    srand(time(0));

    loadPlayerInfo_FromFile("playerinfo.stn");

    std::cout << "Initialize sprites and textures" << std::endl;
    initSpritesAndTextures();

    std::cout << "Initialize fonts" << std::endl;
    initFonts();

    std::cout << "Initialize sounds" << std::endl;
    initSounds();

    std::cout << "Stonar by Tony Shovel" << std::endl;
    std::cout << "My Facebook account: https://facebook.com/tony.shovel.90" << std::endl;
    std::cout << "My Gmail: hcthuynhcongtoai@gmail.com" << std::endl;

    sf::RenderWindow menuWindow(screen, "Stonar by TonyShovel", sf::Style::Fullscreen);
    menuWindow.setMouseCursorVisible(false);
    Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);

    sf::Font font; font.loadFromFile("font/BPPU.TTF");

    sf::Text STONAR("STONAR", font, 75*(scale.x + scale.y)/2);
    STONAR.setColor(sf::Color::Magenta);
    STONAR.setPosition((menuWindow.getSize().x - STONAR.getGlobalBounds().width)/2 , menuWindow.getSize().y * 1/5);

    sf::Vector2f mousePos;
    int option = -1;

    while (menuWindow.isOpen())
    {
        mousePos = sf::Vector2f(sf::Mouse::getPosition(menuWindow));
        mouseSprite.setPosition(mousePos);

        menuWindow.clear();
        menuWindow.draw(sBackground);
        menuWindow.draw(STONAR);
        menu.draw(menuWindow);
        menuWindow.draw(mouseSprite);

        sf::Event event;
        while (menuWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                menuWindow.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    menuWindow.close();
                    break;
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;
                }
                delay(0.02);
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
                    option = menu.GetPressedItem();
                    break;
                }
                delay(0.02);
                break;
            case sf::Event::MouseMoved:
                menu.mouseChoose();
                break;
            case sf::Event::MouseButtonPressed:
                switch (event.key.code)
                {
                case sf::Mouse::Left:
                    option = menu.GetClickedItem();
                    break;
                }
                break;
            }
        }

        //Menu
        switch (option)
        {
        case 0:
            createGame(menuWindow);
            break;
        case 1:
            createUpgradeMenu(menuWindow);
            break;
        case 2:
            savePlayerInfo_ToFile("playerinfo.stn");
            menuWindow.close();
            break;
        }
        option = -1;
        menuWindow.display();
    }
    savePlayerInfo_ToFile("playerinfo.stn");
    return 0;
}
