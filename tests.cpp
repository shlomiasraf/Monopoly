
#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include "Monopoly.hpp"
#include <cassert>

using namespace std;
using namespace ariel;

TEST_CASE("Test all the game")
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Monopoly Game");
    // Test board initialization
    Board board;
    board.createBoard(window);  // Create and initialize the board
    // Create players
    Player* p1 = new Player("Amit", "red",window,1);
    Player* p2 = new Player("Yossi", "blue",window,2);
    Player* p3 = new Player("Dana", "yellow",window,3);

    std::vector<Player*> allPlayers;
    allPlayers.push_back(p1);
    allPlayers.push_back(p2);
    allPlayers.push_back(p3);
    // Initialize the game with 3 players
    Monopoly monopoly({allPlayers});

    // Test starting player selection
    int startingPlayer = monopoly.ChooseStartingPlayer()+1;
    assert(startingPlayer >= 1 && startingPlayer <= 3);


    board.createBoard(window);
    assert(board.getSquares()[0]->getKindAsString() == "Go"); // Test if Go square is created correctly

    // Test player initial position
    assert(p1->currentIndex == 0); // Starting at "Go"

    // Test dice rolling and movement
    monopoly.rollDice(p1,window);
    assert(p1->currentIndex > 0); // Ensure the player moves

    // Test pay for taxSquare
    p2->money = Board::getSquares()[4]->getKind()->process(p2->money);
    assert(p2->money == 1400);

    // Test buy a hotel in Mediterranean Avenue:
    Street *Mediterranean = dynamic_cast<Street *>(Board::getSquares()[1]->getKind());
    p3->money = Mediterranean->buyStreet(p3->money); //street
    p3->ownedProperties.push_back(*(Board::getSquares()[1]));
    p3->money = Mediterranean->buildHouse(p3->money,p3->ownedProperties[0].numberOfHouses); //first house
    p3->ownedProperties[0].numberOfHouses++;
    p3->money = Mediterranean->buildHouse(p3->money,p3->ownedProperties[0].numberOfHouses); //second house
    p3->ownedProperties[0].numberOfHouses++;
    p3->money = Mediterranean->buildHouse(p3->money,p3->ownedProperties[0].numberOfHouses); //3 houses
    p3->ownedProperties[0].numberOfHouses++;
    p3->money = Mediterranean->buildHouse(p3->money,p3->ownedProperties[0].numberOfHouses); //4 houses
    p3->ownedProperties[0].numberOfHouses++;
    p3->money = Mediterranean->buildHouse(p3->money,p3->ownedProperties[0].numberOfHouses); //hotel
    p3->ownedProperties[0].numberOfHouses++;

    assert(p3->ownedProperties[0].numberOfHouses == 5);
    assert(p3->ownedProperties[0].getIndex() == 1);
    assert(p3->money == 1500 - 60 - 108*4 - 100); //street cost + 4 houses + 100 shekels.

    // Check if surpriseCard working
    int moneybefore = p2->money;
    int indexBefore = p2->currentIndex;

    monopoly.surpriseCard1.processCard(p2, allPlayers, window);  // Process surprise card
    assert(moneybefore != p2->money || indexBefore != p2->currentIndex || p2->getOutFromJail);

    // Buy 4 train and check the cost
    Train* train1 = dynamic_cast<Train *>(Board::getSquares()[5]->getKind());
    Train* train2 = dynamic_cast<Train *>(Board::getSquares()[15]->getKind());
    Train* train3 = dynamic_cast<Train *>(Board::getSquares()[25]->getKind());
    Train* train4 = dynamic_cast<Train *>(Board::getSquares()[35]->getKind());

    p2->money = 1500;
    p3->money = 1500;
    p2->money = train1->buyTrain(p2->money);
    p2->numberOfTrains++;
    p2->money = train2->buyTrain(p2->money);
    p2->numberOfTrains++;
    p2->money = train3->buyTrain(p2->money);
    p2->numberOfTrains++;
    p2->money = train4->buyTrain(p2->money);
    p2->numberOfTrains++;
    p3->money = p3->money - train1->process(p2->numberOfTrains);

    assert(p2->numberOfTrains == 4);
    assert(p2->money == 700);
    assert(p3->money == 1300);

    // Test end-game condition
    assert(monopoly.gameIsEnding() == false);  // Ensure game is not ending yet
    std::cout << "All tests passed!" << std::endl;

}