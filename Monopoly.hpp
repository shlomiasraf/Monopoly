//
// Created by Shlomi Asraf on 22/09/2024.
//

#ifndef MONOPOLY_HPP
#define MONOPOLY_HPP
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include "Player.hpp"
namespace ariel
{
    class Monopoly
    {
    private:
        Player& p1;
        Player& p2;
        Player& p3;
        std::vector<Player*> allPlayers;
    public:
        Monopoly(Player&, Player&, Player&);
        void ChooseStartingPlayer();
        std::vector<Player*>& getPlayers();
        void rollDice(Player*,std::vector<Square> squares);
        bool gameIsEnding(Player*);
    };
}
#endif //MONOPOLY_HPP
