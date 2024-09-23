#include "Board.hpp"
#include "Player.hpp"
#include "Monopoly.hpp"

using namespace ariel;

void updateBoard(sf::RenderWindow& window,Board board,std::vector<Player> allPlayers)
{
    window.clear(sf::Color::White);
    board.initializeKindSquare(window);
    for(int i = 0; i < allPlayers.size(); i++)
    {
        allPlayers[i].drawTokenAndInfo(window);
    }
}
int main()
{
    int numPlayers;
    std::vector<std::tuple<std::string, std::string>> playerData;
    std::cout << "Enter number of players between 2-8: ";
    std::cin >> numPlayers;
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
    board.createBoard(window);
    std::vector<Player> allPlayers;
    for (int i = 0; i < numPlayers; i++)
    {
        std::string playerName = std::get<0>(playerData[i]);
        std::string color = std::get<1>(playerData[i]);
        Player player(playerName, color, window, i + 1);
        allPlayers.push_back(player);
    }
    Monopoly monopoly(allPlayers);
    int i = monopoly.ChooseStartingPlayer()-1;   // should print the name of the starting player, assume it is Amit.
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // Handle button clicks
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (board.rollButton.isClicked(window))
                {
                    if(i == allPlayers.size()-1)
                    {
                        i = -1;
                    }
                    i++;
                    monopoly.rollDice(&allPlayers[i],window);
                    updateBoard(window,board,allPlayers);
                }
                if(allPlayers[i].getCurrentSquare()->isPurchasable())
                {
                    if(allPlayers[i].buyButton.isClicked(window))
                    {
                        if(allPlayers[i].handleBuyButtonClick(window))
                        {
                            updateBoard(window, board, allPlayers);
                        }
                    }
                }
            }
        }
        window.display();
    }
}
