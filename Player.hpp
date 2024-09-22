#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <iostream>
#include "kindSquare.hpp"
#include "Square.hpp"

namespace ariel
{
    class Player
    {
    private:
        std::string name;
        std::string color;
        bool hisTurn;
        int money;
        int currentIndex;
        Square currentSquare;
        std::vector<kindSquare> squares;
    public:
        Player();
        Player(std::string,std::string,Square);
        std::string getName();
        std::string getColor();
        void printMoney();
        void endTurn();
        void ChangeToHisTurn(std::vector<Player*>);
        void setCurrentSquare(int numToMove, std::vector<Square> squares);
    };
}

#endif //PLAYER_HPP
