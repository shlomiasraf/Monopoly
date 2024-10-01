#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for seeding random
#include <iostream>
#include "Player.hpp"

namespace ariel
{
    class surpriseCard
    {
    private:
        std::vector<std::string> cards;  // Vector to hold all the surprise cards

    public:
        surpriseCard();  // Constructor to initialize the cards
        std::string getCard() const;  // Method to get a random card
        void addCard();
        void processCard(Player* player,std::vector<Player*>& allplayers, sf::RenderWindow &window);
    };

}

#endif // CARD_HPP
