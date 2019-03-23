#include "upgrade.h"

#include "button.h"
#include "stonar.h"

void modifyMoney(sf::Text &moneyPrinter);
void modifyShotDamage(sf::Text &shotDamagePrinter);
void modifyPrice(sf::Text &pricePrinter);

void createUpgradeMenu(sf::RenderWindow &window)
{
    sf::Texture purchaseTexture;
    purchaseTexture.loadFromFile("img/purchase_button.png");
    sf::Sprite sPurchaseButton(purchaseTexture);
    sPurchaseButton.setScale(0.2, 0.2);

    sf::Text yourmoney("", menuFont, 40*(scale.x + scale.y)/2);
    yourmoney.setColor(sf::Color::Green);
    modifyMoney(yourmoney);

    sf::Text damageText("", menuFont, 35*(scale.x + scale.y)/2);
    damageText.setColor(sf::Color::Cyan);
    modifyShotDamage(damageText);
    damageText.setPosition((screen.width - damageText.getGlobalBounds().width)/2,
                      (screen.height - damageText.getGlobalBounds().height)/2 );

    sf::Text priceText("", menuFont, 15*(scale.x + scale.y)/2);
    priceText.setColor(sf::Color::Red);
    modifyPrice(priceText);
    priceText.setPosition((screen.width - priceText.getGlobalBounds().width)/2,
                          (damageText.getPosition().y + damageText.getGlobalBounds().height + 20)*scale.y);

    sf::Text goBack("BACK", menuFont, 30*(scale.x + scale.y)/2);
    goBack.setColor(sf::Color::White);
    goBack.setPosition((screen.width - goBack.getGlobalBounds().width)*4/5,
                       (screen.height - goBack.getGlobalBounds().height)*7/8);


    Button purchaseButton(sPurchaseButton, sf::Color::White,
                          sf::Vector2f( (screen.width - sPurchaseButton.getGlobalBounds().width)/2,
                                       (priceText.getPosition().y + priceText.getGlobalBounds().height + 20)*scale.y),
                          &window);

    sf::Text notenoughmoney("YOU CANNOT AFFORD IT!", menuFont, 40*(scale.x + scale.y)/2);
    notenoughmoney.setColor(sf::Color::Red);
    notenoughmoney.setOutlineThickness(2.0f);
    notenoughmoney.setOutlineColor(sf::Color::White);
    notenoughmoney.setPosition((screen.width - notenoughmoney.getGlobalBounds().width)/2,
                               (damageText.getPosition().y - 20 - notenoughmoney.getGlobalBounds().height)*scale.y);

    sf::Vector2f mousePos;
    sBackground.setColor(sf::Color::Magenta);

    bool displayYOUCANNOTAFFORD = false;
    while (window.isOpen())
    {
        modifyPrice(priceText);
        modifyShotDamage(damageText);
        modifyMoney(yourmoney);

        mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        mouseSprite.setPosition(mousePos);

        window.clear();

        window.draw(sBackground);
        window.draw(yourmoney);
        window.draw(damageText);
        window.draw(priceText);
        window.draw(goBack);

        if (displayYOUCANNOTAFFORD)
            window.draw(notenoughmoney);

        purchaseButton.draw();
        purchaseButton.changeButtonColor();

        window.draw(mouseSprite);

        window.display();
        standardHandleEvent(window);

        if (goBack.getGlobalBounds().intersects(mouseSprite.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            break;

        if (purchaseButton.isClicked())
        {
            if (currentMoney >= next_Level_Upgrading_Requirement)
            {
                currentMoney -= next_Level_Upgrading_Requirement;
                next_Level_Upgrading_Requirement += 50;
                playerDamage++;

                displayYOUCANNOTAFFORD = false;

                sf::Event release;
                while ( !(window.pollEvent(release) &&
                         release.type == sf::Event::MouseButtonReleased &&
                         release.key.code == sf::Mouse::Left) );
            }
            else
            {
                displayYOUCANNOTAFFORD = true;
            }
        }
    }
    sBackground.setColor(sf::Color::White);
    savePlayerInfo_ToFile("playerinfo.stn");
}

void modifyMoney(sf::Text &moneyPrinter)
{
    char money[100];
    sprintf(money, "YOUR MONEY: %d", currentMoney);
    moneyPrinter.setString(money);
}

void modifyShotDamage(sf::Text &shotDamagePrinter)
{
    char shotdamage[100];
    sprintf(shotdamage, "SHOT DAMAGE: %d", playerDamage);
    shotDamagePrinter.setString(shotdamage);
}

void modifyPrice(sf::Text &pricePrinter)
{
    char price[100];
    sprintf(price, "UPGRADING PRICE: %d", next_Level_Upgrading_Requirement);
    pricePrinter.setString(price);
}
