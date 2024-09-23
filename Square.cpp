#include "Square.hpp"

using namespace ariel;

// Default constructor
Square::Square() : kind(nullptr){}

// Constructor with vertices and kindSquare
Square::Square(int index, kindSquare* kindSquareType,std::string color)
        : index(index), kind(kindSquareType), color(color) {}


// Getter for Vertexs
int Square::getIndex()
{
    return index;
}
std::string Square::getColor()
{
    return color;
}
kindSquare *Square::getKind()
{
    return kind;
}
std::string Square::getKindAsString()
{
    // Check if kind is of type Street, Train, Utility, or other types
    if (dynamic_cast<Street*>(kind) != nullptr)
    {
        return "Street";
    }
    if (dynamic_cast<Train*>(kind) != nullptr)
    {
        return "Train";
    }
    if (dynamic_cast<Utility*>(kind) != nullptr)
    {
        return "Utility";
    }
    if (dynamic_cast<Go*>(kind) != nullptr)
    {
        return "Go";
    }
    if (dynamic_cast<Jail*>(kind) != nullptr)
    {
        return "Jail";
    }
    if (dynamic_cast<Chance*>(kind) != nullptr)
    {
        return "Chance";
    }
    if (dynamic_cast<CommunityChest*>(kind) != nullptr)
    {
        return "CommunityChest";
    }
    if (dynamic_cast<FreeParking*>(kind) != nullptr)
    {
        return "FreeParking";
    }
    if (dynamic_cast<Tax*>(kind) != nullptr)
    {
        return "Tax";
    }
    if (dynamic_cast<GoToJail*>(kind) != nullptr)
    {
        return "GoToJail";
    }

    // If the kind doesn't match any of the known types, return "Unknown"
    return "Unknown";
}
bool Square::isPurchasable()
{
    std::string squareString = getKindAsString();

    // Check if the square is a Street, Train, or Utility (purchasable types)
    if (squareString == "Street" || squareString == "Train" || squareString == "Utility")
    {
        return true; // The square is purchasable
    }

    return false; // The square is not purchasable
}