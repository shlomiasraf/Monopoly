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
        std::vector<Player> allPlayers;
    public:
        Monopoly(std::vector<Player>);
        int ChooseStartingPlayer();
        void rollDice(Player*,sf::RenderWindow &window);
        bool gameIsEnding(Player*);
    };
}
#endif //MONOPOLY_HPP
