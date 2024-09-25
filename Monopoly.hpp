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
        std::vector<Player*>& allPlayers;  // Reference to the vector of Player pointers

    public:
        Monopoly(std::vector<Player*>&);  // Constructor accepts reference to vector of Player pointers
        int ChooseStartingPlayer();  // Randomly chooses a starting player
        void rollDice(Player*, sf::RenderWindow &window);  // Rolls the dice for a player
        bool gameIsEnding(Player*);  // Checks if the game is ending for a given player
    };
}

#endif //MONOPOLY_HPP
