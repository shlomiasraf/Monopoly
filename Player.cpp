

#include "Player.hpp"

using namespace ariel;

Player::Player() = default;

Player::Player(std::string name,std::string color,Square currentSquare)
{
    this->name = name;
    this->color = color;
    this->money = 1500;
    this->currentIndex = 0;
    this->currentSquare = currentSquare;
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
void Player::setCurrentSquare(int numToMove, std::vector<Square> squares)
{
    if(currentIndex+numToMove >= squares.size())
    {
        this->currentSquare = squares[currentIndex+numToMove-squares.size()];
        currentIndex = currentIndex+numToMove-squares.size();

    }
    else
    {
        this->currentSquare = squares[currentIndex+numToMove];
        currentIndex += numToMove;
    }
}
