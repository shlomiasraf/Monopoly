#include "kindSquare.hpp"

// Implementation of Street class
Street::Street(const std::string& name, int price, int rent, int houseCost, int rentWithHouse, int rentWithHotel, ColorGroup colorGroup)
    : name(name), price(price), rent(rent), houseCost(houseCost), rentWithHouse(rentWithHouse), rentWithHotel(rentWithHotel), colorGroup(colorGroup) {}

void Street::process() const
{
    // Implementation for processing a street square
}

// Implementation of Train class
Train::Train(const std::string& name, int cost)
    : name(name), cost(cost) {}

void Train::process() const {
    // Implementation for processing a train square
}

// Implementation of Go class
void Go::process() const {
    // Implementation for processing the GO square
}

// Implementation of Jail class
Jail::Jail() : turnsInJail(0) {}

void Jail::process() const {
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
void Chance::process() const {
    // Implementation for processing a chance square
}

// Implementation of CommunityChest class
void CommunityChest::process() const {
    // Implementation for processing a CommunityChest square
}

// Implementation of FreeParking class
void FreeParking::process() const {
    // Implementation for processing a free parking square
}

// Implementation of Tax class
Tax::Tax(const std::string& name, int cost) : name(name), cost(cost) {}

void Tax::process() const {
    // Implementation for processing a tax square
}

// Implementation of GoToJail class
void GoToJail::process() const {
    // Implementation for processing a go to jail square
}

// Implementation of Utility class
Utility::Utility(const std::string& name, int cost)
    : name(name), cost(cost) {}

void Utility::process() const {
    // Implementation for processing a utility square
}
