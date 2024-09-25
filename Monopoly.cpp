//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Monopoly.hpp"

using namespace ariel;

// Constructor takes reference to vector of Player pointers
Monopoly::Monopoly(std::vector<Player*>& allplayers)
        : allPlayers(allplayers)  // Initialize the reference
{
}

int Monopoly::ChooseStartingPlayer()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, allPlayers.size()-1);  // Randomly select a player
    int randomNumber = dis(gen);
    std::cout << allPlayers[randomNumber]->getName() << " you start the game." << "\n";  // Output the starting player
    return randomNumber;
}

void Monopoly::rollDice(Player* player, sf::RenderWindow &window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    int cube1 = dis(gen);
    std::uniform_int_distribution<> dis2(1, 6);
    int cube2 = dis2(gen);
    int randomNumber = cube1 + cube2;  // Calculate the total roll

    // Reset all players' turn status
    for (int i = 0; i < allPlayers.size(); i++)
    {
        allPlayers[i]->hisTurn = false;
        if (allPlayers[i] == player)
        {
            if (i == 0)
            {
                allPlayers[allPlayers.size() - 1]->hisTurn = false;
                break;
            }
        }
    }

    player->hisTurn = true;  // Set the current player's turn to true
    player->setCurrentSquare(randomNumber, window);  // Move player to new square

    bool found = false;
    if(player->getCurrentSquare()->isPurchasable())
    {
        if(player->getCurrentSquare()->ownerColor != "None" && player->getCurrentSquare()->ownerColor != player->getColor()) {
            for (auto &otherPlayer: allPlayers) {
                if (otherPlayer->getColor() != player->getColor() &&
                    player->getCurrentSquare()->ownerColor == otherPlayer->getColor())  // Check other players
                {
                    int moveToFunction = 0;
                    if (player->getCurrentSquare()->getKindAsString() == "Street") {
                        moveToFunction = player->getCurrentSquare()->numberOfHouses;
                    } else if (player->getCurrentSquare()->getKindAsString() == "Train") {
                        moveToFunction = player->numberOfTrains;
                    } else {
                        moveToFunction = randomNumber;
                    }
                    int cost = player->getCurrentSquare()->getKind()->process(moveToFunction);
                    otherPlayer->money += cost;
                    player->money -= cost;
                    break;
                }
            }
        }
    }
    else
    {
        player->money = player->getCurrentSquare()->getKind()->process(player->money);
    }
    std::cout << "The roll dice in " << player->getName() << "'s turn, with color " << player->getColor() << " is: " << randomNumber << "\n";
}
bool Monopoly::gameIsEnding(Player* player)
{
    // Define the logic to determine if the game is ending based on player's state
    return false;
}
