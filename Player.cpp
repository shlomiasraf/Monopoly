

#include "Player.hpp"

using namespace ariel;

Player::Player() = default;

Player::Player(std::string name,std::string color)
{
    this->name = name;
    this->color = color;
    this->money = 1500;
    this->currentIndex = 0;
    this->currentSquare = Board::getSquares()[currentIndex];
}
std::string Player::getColor()
{
    return this->color;
}
std::string Player::getName()
{
    return this->name;
}

void Player::endTurn()
{
    hisTurn = false;
}
void Player::printMoney()
{
    std::cout<< "the total money of " << this->name << " with color " << this->color << " is: " << this->money << "\n";
}
void Player::ChangeToHisTurn(std::vector<Player*> allPlayers)
{
    for(int i = 0; i < allPlayers.size(); i++)
    {
        if(allPlayers[i]->color != this->color)
        {
            allPlayers[i]->endTurn();
        }
    }
    this->hisTurn = true;

}
void Player::setCurrentSquare(int numToMove)
{
    if(currentIndex+numToMove >= Board::getSquares().size())
    {
        this->currentSquare = Board::getSquares()[currentIndex+numToMove-Board::getSquares().size()];
        currentIndex = currentIndex+numToMove-Board::getSquares().size();

    }
    else
    {
        this->currentSquare = Board::getSquares()[currentIndex+numToMove];
        currentIndex += numToMove;
    }
}
