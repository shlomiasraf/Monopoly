//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Monopoly.hpp"

using namespace ariel;

// Constructor takes reference to vector of Player pointers
/**
 * @brief Constructor for the Monopoly class.
 * @param allplayers A reference to a vector of Player pointers representing all the players in the game.
 *
 * This constructor initializes the Monopoly game with a reference to all the players.
 */
Monopoly::Monopoly(std::vector<Player*>& allplayers)
        : allPlayers(allplayers)  // Initialize the reference
{
}

// Choose the starting player for this game.
/**
 * @brief Randomly selects a player to start the game.
 * @return The index of the starting player.
 *
 * This method randomly selects a player from the list of players and returns their index.
 * It uses a random number generator to select a player and announces the starting player.
 */
int Monopoly::ChooseStartingPlayer()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, allPlayers.size()-1);  // Randomly select a player
    int randomNumber = dis(gen);
    std::cout << allPlayers[randomNumber]->getName() << " you start the game." << "\n";  // Output the starting player
    return randomNumber;
}

// Roll Dice for the player
/**
 * @brief Rolls two dice for the current player and processes the player's move.
 * @param player A pointer to the Player object representing the current player.
 * @param window A reference to the SFML render window for graphical updates.
 *
 * This method simulates rolling two dice and moves the player based on the result. If the player rolls doubles three times in a row,
 * they are sent to jail. If the player is in jail, the method handles jail mechanics, including using a 'Get Out of Jail Free' card,
 * paying a fine, or rolling doubles to get out. The player's new position is determined and any relevant effects, such as landing on
 * a purchasable square or encountering a chance card, are processed.
 */
void Monopoly::rollDice(Player* player, sf::RenderWindow &window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    int cube1 = dis(gen);
    std::uniform_int_distribution<> dis2(1, 6);
    int cube2 = dis2(gen);
    int randomNumber = cube1 + cube2;  // Calculate the total roll

    // If player rolls doubles and is not in jail
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

    // Handle if player rolled three doubles in a row
    if(player->doubleInRow == 3)
    {
        player->turnsInJail = 3;
        player->doubleInRow = 0;
        std::cout << "you have 3 doubles in row Go to jail! Move directly to jail and skip 3 turns.\n";
        player->setCurrentSquare(20, window);  // Move player to jail
    }
        // Handle if player is currently in jail
    else if(player->getCurrentSquare()->getKindAsString() == "Jail" && player->turnsInJail != 0)
    {
        if(cube1 == cube2)
        {
            player->turnsInJail = 0;
            std::cout << player->getName() << " rolled a double and is out of jail!\n";
        }
        else if(player->getOutFromJail)
        {
            player->turnsInJail = 0;
            std::cout << player->getName() << " you have the 'get out card' now you are out of jail!\n";
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
        // Move player to new square based on dice roll
        player->setCurrentSquare(randomNumber, window);

        // Handle landing on Chance or Community Chest
        if(player->getCurrentSquare()->getKindAsString() == "Chance" || player->getCurrentSquare()->getKindAsString() == "CommunityChest")
        {
            player->money = player->getCurrentSquare()->getKind()->process(player->money);
            surpriseCard1.processCard(player, allPlayers, window);  // Process surprise card
        }

        // Handle purchasing or paying rent
        if (player->getCurrentSquare()->isPurchasable())
        {
            if (player->getCurrentSquare()->ownerColor != "None" && player->getCurrentSquare()->ownerColor != player->getColor())
            {
                for (auto &otherPlayer: allPlayers)
                {
                    if (otherPlayer->getColor() != player->getColor() &&
                        player->getCurrentSquare()->ownerColor == otherPlayer->getColor())
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
                        if(player->money < 0)
                        {
                            for(int i = 0; i < player->ownedProperties.size(); i++)
                            {
                                player->ownedProperties[i].ownerColor = otherPlayer->getColor();
                                otherPlayer->ownedProperties.push_back(player->ownedProperties[i]);
                                player->ownershipMarkers[i].setFillColor(otherPlayer->token.getFillColor());
                                otherPlayer->ownershipMarkers.push_back(player->ownershipMarkers[i]);
                            }
                        }
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
                player->setCurrentSquare(20, window);  // Move player to jail
            }
        }
    }
    if(player->money < 0)
    {
        player->sizeMarkers = 0;
        player->ownedProperties.clear();
        player->ownershipMarkers.clear();
    }
    std::cout << "The roll dice in " << player->getName() << "'s turn, with color " << player->getColor() << " is: " << randomNumber << "\n";
}

// Check if the game has ended
/**
 * @brief Checks if the game has reached its end.
 * @return true if the game is over, false otherwise.
 *
 * This method checks the players' money to determine if only one player is left with non-negative money,
 * indicating the game has ended. If the game is ending, the winner is announced.
 */
bool Monopoly::gameIsEnding()
{
    int countInTheGame = 0;
    int playerWhoWinByMoney = 0;
    std::string winner = "";
    for (int i = 0; i < allPlayers.size(); i++)
    {
        if(allPlayers[i]->money >= 0)
        {
            countInTheGame++;
            winner = allPlayers[i]->getName();
        }
        if(allPlayers[i]->money >= 4000)
        {
    	    playerWhoWinByMoney++;
            winner = allPlayers[i]->getName();
        }
    }
    if(countInTheGame > 1 && playerWhoWinByMoney == 0)
    {
        return false;
    }
    std::cout << "The name of the winner is: " + winner + "\n";
    return true;
}
