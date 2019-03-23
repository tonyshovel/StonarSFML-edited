
#include "encrypted.h"

std::string Encrypting::reverseStr(std::string str)
{
    int n = str.length();

    for (int i = 0; i < n/2; i++)
        std::swap(str[i], str[n-i-1]);
    return str;
}

std::string Encrypting::encrypt(int number)
{
    std::vector<std::string> lib = { "23r0", "w4nt", "trU3", "tr33", "for", "f1n3", "51ck", "53^3n", "319ht", "n19ht" };
    std::string result;

    while (number)
    {
        result += (lib.at(lib.size() - number%10 - 1) + "%");
        number /= 10;
    }

    return reverseStr(result);
}

int Encrypting::findNumInLib(std::vector<std::string> lib, std::string num)
{
    for (int i(0); i < lib.size(); i++)
    {
        if (num == lib.at(i))
            return i;
    }
    return -1;
}

int Encrypting::decrypt(std::string text)
{
    std::vector<std::string> lib = { "23r0", "w4nt", "trU3", "tr33", "for", "f1n3", "51ck", "53^3n", "319ht", "n19ht" };
    std::string str = reverseStr(text);

    int result = 0;
    int mul = 1;
    while (str.size())
    {
        std::size_t pos = str.find("%");
        std::string numText = str.substr(0, pos);
        str.erase(0, pos + 1);

        result += (lib.size() - findNumInLib(lib, numText) - 1)*mul;
        mul *= 10;
    }
    return result;
}
