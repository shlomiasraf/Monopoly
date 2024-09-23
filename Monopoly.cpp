//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Monopoly.hpp"


using namespace ariel;


Monopoly::Monopoly(std::vector<Player> allplayers)
{
    this->allPlayers = std::move(allplayers);
}

int Monopoly::ChooseStartingPlayer()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, allPlayers.size()-1);
    int randomNumber = dis(gen);
    std::cout<<  allPlayers[randomNumber].getName() << " you start the game." << "\n";
    return randomNumber;
}
void Monopoly::rollDice(Player* player,sf::RenderWindow &window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    int cube1 = dis(gen);
    std::uniform_int_distribution<> dis2(1, 6);
    int cube2 = dis2(gen);
    int randomNumber = cube1 + cube2;
    for(int i = 0; i < allPlayers.size(); i++)
    {
        allPlayers[i].hisTurn = false;
        if(&allPlayers[i] == player)
        {
            if(i == 0)
            {
                allPlayers[allPlayers.size()-1].hisTurn = false;
                break;
            }
        }
    }
    player->hisTurn = true;
    player->setCurrentSquare(randomNumber,window);
    bool found = false;
    for(auto& otherPlayer : allPlayers)
    {
        if(&otherPlayer != player)
        {
            for(auto Square : otherPlayer.ownedProperties)
            {
                if(Square.getIndex() == player->getCurrentSquare()->getIndex())
                {
                    otherPlayer.money += player->money - (player->getCurrentSquare()->getKind()->process(player->money));
                    player->money = player->getCurrentSquare()->getKind()->process(player->money);
                    found = true;
                    break;
                }
            }
        }
        if(found)
        {
            break;
        }
    }
    std::cout<< "the roll dice in " << player->getName() << "'s turn " << "with color " << player->getColor() <<  " is: " << randomNumber << "\n";
}
bool Monopoly::gameIsEnding(Player* player)
{
    return false;
}