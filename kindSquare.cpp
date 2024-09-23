#include "kindSquare.hpp"
using namespace ariel;

// Implementation of Street class
Street::Street(const std::string& name, int price, int rent, int houseCost, int rentWithHouse, int rentWithHotel, ColorGroup colorGroup)
    : name(name), price(price), rent(rent), houseCost(houseCost), rentWithHouse(rentWithHouse), rentWithHotel(rentWithHotel), colorGroup(colorGroup) {}

int Street::process(int money) const
{
    return money-price;
}
int Street::rentToOther(int money,int numOfHouses)
{
    return money-rent;
}
int Street::buildHouse(int money,int numOfHouses)
{
    return money-houseCost;
}
// Implementation of Train class
Train::Train(const std::string& name, int cost)
    : name(name), cost(cost) {}

int Train::process(int money) const
{
    return money-cost;
}

// Implementation of Go class
int Go::process(int money) const
{
    // Implementation for processing the GO square
}

// Implementation of Jail class
Jail::Jail() : turnsInJail(0) {}

int Jail::process(int money) const
{
    // Logic for what happens when the player lands in jail
}

int Jail::getTurnsInJail() const {
    return turnsInJail;
}

void Jail::incrementTurns() {
    turnsInJail++;
    if (turnsInJail >= 3) {
        turnsInJail = 0; // Reset after 3 turns
    }
}

// Implementation of Chance class
int Chance::process(int money) const {
    // Implementation for processing a chance square
}

// Implementation of CommunityChest class
int CommunityChest::process(int money) const {
    // Implementation for processing a CommunityChest square
}

// Implementation of FreeParking class
int FreeParking::process(int money) const {
    // Implementation for processing a free parking square
}

// Implementation of Tax class
Tax::Tax(const std::string& name, int cost) : name(name), cost(cost) {}

int Tax::process(int money) const {
    // Implementation for processing a tax square
}

// Implementation of GoToJail class
int GoToJail::process(int money) const {
    // Implementation for processing a goto jail square
}

// Implementation of Utility class
Utility::Utility(const std::string& name, int cost)
    : name(name), cost(cost) {}

int Utility::process(int money) const
{
    return money-cost;
}
