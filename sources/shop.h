#ifndef _shop_header
#define _shop_header

#include <vector>

class Item
{
};

class Store
{
public:
    std::vector<Item> items;
};

typedef std::vector<Store> Shop;


#endif // _shop_header
