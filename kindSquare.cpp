#include <iostream>
#include "kindSquare.hpp"

using namespace ariel;

// ********** Street Class Implementation **********
Street::Street(const std::string& name, int price, int rent, int houseCost, int rentWithHouse, int rentWithHotel, ColorGroup colorGroup)
        : name(name), price(price), rent(rent), houseCost(houseCost), rentWithHouse(rentWithHouse), rentWithHotel(rentWithHotel), colorGroup(colorGroup) {}

int Street::process(int numOfHouses) const {
    if (numOfHouses == 0) {
        return rent;
    } else if (numOfHouses == 5) {
        return rentWithHotel;  // Rent with hotel
    } else {
        return rentWithHouse * std::pow(2, numOfHouses - 1);  // Rent increases exponentially with houses
    }
}

int Street::buildHouse(int money, int numOfHouses) {
    if (numOfHouses < 4) {
        return money - houseCost;  // Build a house
    } else if (numOfHouses == 4) {
        return money - houseCost - 100;  // Build a hotel (4 houses + 100 extra cost)
    }
    return money;
}

int Street::buyStreet(int money)
{
    return money - price;  // Deduct the cost of the street from the player's money
}

// ********** Train Class Implementation **********
Train::Train(const std::string& name, int cost)
        : name(name), cost(cost) {}

int Train::process(int numOfTrains) const {
    switch (numOfTrains) {
        case 1: return 50;
        case 2: return 100;
        case 3: return 150;
        case 4: return 200;
        default: return 0;
    }
}

int Train::buyTrain(int money)
{
    return money - cost;  // Deduct the cost of the train from the player's money
}

// ********** Chance Class Implementation **********
int Chance::process(int money) const {
    // Implement dynamic behavior with chance cards (placeholder)
    int outcome = rand() % 3;  // Random outcome for the chance
    switch (outcome) {
        case 0:
            std::cout << "You received a Get Out of Jail Free card!\n";
            break;
        case 1:
            std::cout << "You received a bonus of 200!\n";
            return money + 200;
        case 2:
            std::cout << "Pay 50 for a speeding ticket.\n";
            return money - 50;
    }
    return money;
}

// ********** CommunityChest Class Implementation **********
int CommunityChest::process(int money) const {
    // Example dynamic behavior for the community chest
    std::cout << "You received 100 from the Community Chest!\n";
    return money + 100;
}

// ********** FreeParking Class Implementation **********
int FreeParking::process(int money) const {
    // No money changes hands, just a free stop
    std::cout << "You're on Free Parking! Enjoy the rest.\n";
    return money;
}

// ********** Tax Class Implementation **********
Tax::Tax(const std::string& name, int cost)
        : name(name), cost(cost) {}

int Tax::process(int money) const
{
    std::cout << "You need to pay a tax of " << cost << ".\n";
    return money - cost;
}

// ********** GoToJail Class Implementation **********
int GoToJail::process(int money) const
{
    std::cout << "Go to jail! Move directly to jail and skip 3 turns.\n";
    return money;  // No immediate monetary effect
}

// ********** Utility Class Implementation **********
Utility::Utility(const std::string& name, int cost)
        : name(name), cost(cost) {}

int Utility::process(int diceRoll) const
{
    std::cout << "You rolled " << diceRoll << " and owe " << diceRoll * 10 << ".\n";
    return diceRoll * 10;
}
int Utility::buyUtility(int money)
{
    return money - cost;  // Deduct the cost of the train from the player's money
}

// ********** Jail Class Implementation **********
Jail::Jail() : turnsInJail(0) {}

int Jail::process(int money) const {
    std::cout << "You are in jail for " << turnsInJail << " turns.\n";
    if (turnsInJail < 3) {
        std::cout << "You can pay 50 or roll for a double to get out.\n";
    } else {
        std::cout << "You must pay 50 to get out after 3 turns.\n";
        return money - 50;
    }
    return money;
}

int Jail::getTurnsInJail() const {
    return turnsInJail;
}

void Jail::incrementTurns() {
    turnsInJail++;
    if (turnsInJail >= 3) {
        turnsInJail = 0;  // Reset after 3 turns
    }
}
// Implementation of Go class
int Go::process(int money) const
{
    return money;
}
