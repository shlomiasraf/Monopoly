//
// Created by Shlomi Asraf on 28/05/2024.
//

#include "Monopoly.hpp"


using namespace ariel;

Monopoly::Monopoly(Player& player1, Player& player2, Player& player3)
    : p1(player1), p2(player2), p3(player3)
{
}
void Monopoly::ChooseStartingPlayer()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 3);
    int randomNumber = dis(gen);
    if(randomNumber == 1)
    {
        this->allPlayers.push_back(&p1);
        this->allPlayers.push_back(&p2);
        this->allPlayers.push_back(&p3);
        p1.ChangeToHisTurn(allPlayers);
        std::cout<< p1.getName() << " you start the game." << "\n";
    }
    else if (randomNumber == 2)
    {
        this->allPlayers.push_back(&p2);
        this->allPlayers.push_back(&p3);
        this->allPlayers.push_back(&p1);
        p2.ChangeToHisTurn(allPlayers);
        std::cout<< p2.getName() << " you start the game." << "\n";
    }
    else
    {
        allPlayers.push_back(&p3);
        allPlayers.push_back(&p1);
        allPlayers.push_back(&p2);
        p3.ChangeToHisTurn(allPlayers);
        std::cout<< p3.getName() << " you start the game." << "\n";
    }
}
std::vector<Player*>& Monopoly::getPlayers()
{
    return this->allPlayers;
}
void Monopoly::rollDice(Player* player1,std::vector<Square> squares)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    int cube1 = dis(gen);
    std::uniform_int_distribution<> dis2(1, 6);
    int cube2 = dis2(gen);
    int randomNumber = cube1 + cube2;
    player1->ChangeToHisTurn(allPlayers);
    player1->setCurrentSquare(randomNumber,squares);
    std::cout<< "the roll dice in " << player1->getName() << "'s turn " << "with color " << player1->getColor() <<  " is: " << randomNumber << "\n";
}
bool Monopoly::gameIsEnding(Player* player)
{
    return false;
}