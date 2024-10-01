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
// Choose the starting player for this game.

int Monopoly::ChooseStartingPlayer()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, allPlayers.size()-1);  // Randomly select a player
    int randomNumber = dis(gen);
    std::cout << allPlayers[randomNumber]->getName() << " you start the game." << "\n";  // Output the starting player
    return randomNumber;
}
//roll Dice for the player

void Monopoly::rollDice(Player* player, sf::RenderWindow &window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    int cube1 = dis(gen);
    std::uniform_int_distribution<> dis2(1, 6);
    int cube2 = dis2(gen);
    int randomNumber = cube1 + cube2;  // Calculate the total roll

    if (cube1 == cube2 && player->turnsInJail == 0)
    {
        player->doubleInRow++;
    }
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
    if(player->doubleInRow == 3)
    {
        player->turnsInJail = 3;
        player->doubleInRow = 0;
        std::cout << "you have 3 doubles in row Go to jail! Move directly to jail and skip 3 turns.\n";
        player->setCurrentSquare(20, window);  // Move player to new square
    }
    else if(player->getCurrentSquare()->getKindAsString() == "Jail" && player->turnsInJail != 0)
    {
        if(cube1 == cube2)
        {
            player->turnsInJail = 0;
            std::cout << player->getName() << " rolled a double and is out of jail!\n";
        }
        if(player->getOutFromJail)
        {
            player->turnsInJail = 0;
            std::cout << player->getName() << " you have the 'get out card' now you out of jail!\n";
            player->getOutFromJail = false;
        }
        else
        {
            char choice;
            std::cout << "Do you want to pay the fine of 50 to exit jail early? (y/n): ";
            std::cin >> choice;
            if ((choice == 'y' || choice == 'Y') && player->money > 50) {
                player->turnsInJail = 0;
                player->money = player->getCurrentSquare()->getKind()->process(player->money);
            } else {
                player->turnsInJail--;
                if (player->turnsInJail == 0) {
                    player->money = player->getCurrentSquare()->getKind()->process(player->money);
                }
            }
        }
    }
    else
    {
        player->setCurrentSquare(randomNumber, window);  // Move player to new square
        if(player->getCurrentSquare()->getKindAsString() == "Chance" || player->getCurrentSquare()->getKindAsString() == "CommunityChest")
        {
            player->money = player->getCurrentSquare()->getKind()->process(player->money);
            surpriseCard1.processCard(player,allPlayers,window);
        }
        if (player->getCurrentSquare()->isPurchasable())
        {
            if (player->getCurrentSquare()->ownerColor != "None" && player->getCurrentSquare()->ownerColor != player->getColor())
            {
                for (auto &otherPlayer: allPlayers) {
                    if (otherPlayer->getColor() != player->getColor() &&
                        player->getCurrentSquare()->ownerColor == otherPlayer->getColor())  // Check other players
                    {
                        int moveToFunction;
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
            if(player->getCurrentSquare()->getKindAsString() != "Chance" && player->getCurrentSquare()->getKindAsString() != "CommunityChest")
            {
                player->money = player->getCurrentSquare()->getKind()->process(player->money);
            }
            if (player->getCurrentSquare()->getKindAsString() == "GoToJail")
            {
                player->turnsInJail = 3;
                player->setCurrentSquare(20, window);  // Move player to new square
            }
        }
    }
    std::cout << "The roll dice in " << player->getName() << "'s turn, with color " << player->getColor() << " is: " << randomNumber << "\n";
}
bool Monopoly::gameIsEnding()
{
    int countInTheGame = 0;
    std::string winner = "";
    for (int i = 0; i < allPlayers.size(); i++)
    {
        if(allPlayers[i]->money >= 0)
        {
            countInTheGame++;
            winner = allPlayers[i]->getName();
        }
    }
    if(countInTheGame > 1)
    {
        return false;
    }
    std::cout << "The name of the winner is: " + winner;
    return true;
}