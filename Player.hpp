#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Square.hpp"
#include "Board.hpp"
#include "Button.hpp"

namespace ariel
{
    class Player
    {
    private:
        std::string name;
        std::string color;
        Square* currentSquare;
        sf::Text playerInfo;
        bool nowBuy;
    public:
        bool getOutFromJail = false;
        int currentIndex;
        int doubleInRow = 0;
        int turnsInJail = 0;
        int numberOfTrains = 0;
        int serialNum;
        bool hisTurn = false;
        int sizeMarkers = 0;
        sf::CircleShape token;
        std::vector<Square> ownedProperties; // To store owned properties
        std::vector<sf::CircleShape> ownershipMarkers; // Vector to store ownership markers
        Button buyButton;
        int money;
        Player(std::string name, std::string color, sf::RenderWindow &window, int serialNum);
        virtual ~Player() = default; // Virtual destructor for proper cleanup of derived class objects
        std::string getName();
        std::string getColor();
        Square* getCurrentSquare();
        void setCurrentSquare(int numToMove, sf::RenderWindow &window);
        void initializePlayerToken(sf::RenderWindow &window);
        void drawTokenAndInfo(sf::RenderWindow &window);
        void drawBuyButton(sf::RenderWindow &window);
        bool handleBuyButtonClick(sf::RenderWindow &window);
        bool checkIfCanBuildHouse();
        bool checkIfCanBuildHotel();
    };
}

#endif // PLAYER_HPP