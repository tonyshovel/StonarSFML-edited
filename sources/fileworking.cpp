#include "stonar.h"

#include <fstream>
#include <string>

#include "encrypted.h"

std::string playerName = "";
int playerDamage = 0;
int currentMoney = 0;
int next_Level_Upgrading_Requirement = 0;

void loadPlayerInfo_FromFile(std::string path)
{
    std::ifstream playerInfo(path);
    if (!playerInfo)
    {
        std::cout << "Cannot open playerinfo.stn" << std::endl;
        exit(1);
    }

    std::string temp;

    std::getline(playerInfo, playerName);

    std::getline(playerInfo, temp);
    playerDamage = Encrypting::decrypt(temp);

    std::getline(playerInfo, temp);
    currentMoney = Encrypting::decrypt(temp);

    std::getline(playerInfo, temp);
    next_Level_Upgrading_Requirement = Encrypting::decrypt(temp);

    playerInfo.close();
}

void savePlayerInfo_ToFile(std::string path)
{
    std::ofstream playerInfo(path);
    if (!playerInfo)
    {
        std::cout << "Cannot open playerinfo.stn" << std::endl;
        exit(1);
    }

    playerInfo << playerName << std::endl;
    playerInfo << Encrypting::encrypt(playerDamage) << std::endl;
    playerInfo << Encrypting::encrypt(currentMoney) << std::endl;
    playerInfo << Encrypting::encrypt(next_Level_Upgrading_Requirement) << std::endl;

    playerInfo.close();
}
