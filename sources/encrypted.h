#ifndef _encrypted_header
#define _encrypted_header

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

namespace Encrypting
{
    std::string reverseStr(std::string str);
    std::string encrypt(int number);

    int decrypt(std::string text);
    int findNumInLib(std::vector<std::string> lib, std::string num);
}

#endif // _encrypted_header
