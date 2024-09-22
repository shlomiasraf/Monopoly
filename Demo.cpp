/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Monopoly.hpp"
#include "Player.hpp"
#include "Board.hpp"
using namespace std;
using namespace ariel;

int main()
{
    Board board;// get the board of the game.
    board.createBoard();
    Player p1("Amit","red");
    Player p2("Yossi","blue");
    Player p3("Dana","yellow");
    Monopoly monopoly(p1, p2, p3);
    monopoly.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    vector<Player*> allPlayers = monopoly.getPlayers();
    int i = 0;
    while(!monopoly.gameIsEnding(allPlayers[i]))
    {
        monopoly.rollDice(allPlayers[i]);
        if(i < 2)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
//    allPlayers[0]->printPoints();
  //  allPlayers[1]->printPoints();
  //  allPlayers[2]->printPoints();

}
