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
        int currentIndex;
        Square* currentSquare;
        sf::CircleShape token;
        std::vector<sf::CircleShape> ownershipMarkers; // Vector to store ownership markers
        int sizeMarkers = 0;
        sf::Text playerInfo;
        bool nowBuy;
    public:
        int numberOfTrains = 0;
        int serialNum;
        bool hisTurn = false;
        std::vector<Square> ownedProperties; // To store owned properties
        Button buyButton;
        int money;
        Player(std::string name, std::string color, sf::RenderWindow &window, int serialNum);
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
