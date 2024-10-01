#include "Board.hpp"
#include "Player.hpp"
#include "Monopoly.hpp"

using namespace ariel;

void updateBoard(sf::RenderWindow& window, Board& board, std::vector<Player*>& allPlayers)
{
    window.clear(sf::Color::White);
    board.initializeKindSquare(window);  // Initialize the squares on the board
    for (int i = 0; i < allPlayers.size(); i++)
    {
        allPlayers[i]->drawTokenAndInfo(window);  // Draw the player's token and info
    }
}

int main()
{
    int numPlayers;
    std::vector<std::tuple<std::string, std::string>> playerData;
    std::cout << "Enter number of players between 2-8: ";
    std::cin >> numPlayers;
    // Check if the input is a valid integer
    if (std::cin.fail()) {
        std::cout << "Invalid input detected. Exiting the program." << std::endl;
        exit(1);  // Exit the program if the input is not a number
    }
    while(numPlayers < 2 || numPlayers > 8)
    {
        std::cout << "Please enter again number of players between 2-8: ";
        std::cin >> numPlayers;
        // Check if the input is a valid integer
        if (std::cin.fail()) {
            std::cout << "Invalid input detected. Exiting the program." << std::endl;
            exit(1);  // Exit the program if the input is not a number
        }
    }
    // Collect player name and color for each player
    for (int i = 0; i < numPlayers; i++)
    {
        std::string playerName, color;
        std::cout << "Enter name and color for player " << i + 1 << ": ";
        std::cin >> playerName >> color;
        playerData.push_back(std::make_tuple(playerName, color));
    }

    sf::RenderWindow window(sf::VideoMode(800, 800), "Monopoly Game");
    window.clear(sf::Color::White);
    Board board;
    board.createBoard(window);  // Create and initialize the board
    std::vector<Player*> allPlayers;

    // Create players using the collected data and add pointers to the vector allPlayers
    for (int i = 0; i < numPlayers; i++)
    {
        std::string playerName = std::get<0>(playerData[i]);
        std::string color = std::get<1>(playerData[i]);
        Player* player = new Player(playerName, color, window, i + 1);  // Create a new player
        allPlayers.push_back(player);  // Add pointer to the player vector
    }

    Monopoly monopoly(allPlayers);
    int i = monopoly.ChooseStartingPlayer() - 1;  // Choose the starting player

    while (window.isOpen() && !monopoly.gameIsEnding())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse button click events
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (board.rollButton.isClicked(window))
                {
                    if (i == allPlayers.size() - 1)
                    {
                        i = -1;
                    }
                    i++;
                    if(allPlayers[i]->money >= 0)
                    {
                        monopoly.rollDice(allPlayers[i], window);  // Roll dice for the current player
                    }
                    updateBoard(window, board, allPlayers);  // Update the board with the player's information
                }

                // If the player lands on a purchasable square, handle the purchase
                if (allPlayers[i]->money >= 0 && allPlayers[i]->getCurrentSquare()->isPurchasable())
                {
                    if (allPlayers[i]->buyButton.isClicked(window))
                    {
                        if (allPlayers[i]->handleBuyButtonClick(window))
                        {
                            updateBoard(window, board, allPlayers);  // Update the board after a purchase
                        }
                    }
                }
            }
        }
        window.display();  // Display the updated game window
    }

    // Clean up memory by deleting the players created with new
    for (Player* player : allPlayers)
    {
        delete player;
    }
}
