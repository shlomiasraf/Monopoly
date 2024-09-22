#ifndef KINDSQUARE_HPP
#define KINDSQUARE_HPP

#include <string>

// Enumeration for color groups
enum class ColorGroup
{
    Brown,
    LightBlue,
    Pink,
    Orange,
    Red,
    Yellow,
    Green,
    Blue,
};

// Base abstract class
class kindSquare
{
public:
    virtual ~kindSquare() = default; // Virtual destructor for proper cleanup of derived class objects
    virtual void process() const = 0; // Pure virtual function for specific behavior of different square types
};

// Street class
class Street : public kindSquare
{
public:
    Street(const std::string& name, int price, int rent, int houseCost, int rentWithHouse, int rentWithHotel, ColorGroup colorGroup);
    void process() const override;

private:
    std::string name;                // Name of the street
    int price;                       // Price to buy the street
    int rent;                        // Rent when no houses or hotels are built
    int houseCost;                   // Cost to build a house on the street
    int rentWithHouse;               // Rent with one or more houses
    int rentWithHotel;               // Rent with a hotel
    ColorGroup colorGroup;           // Color group to which the street belongs
};

// Train class
class Train : public kindSquare
{
public:
    Train(const std::string& name, int cost); // Constructor declaration
    void process() const override;

private:
    std::string name;                // Name of the train
    int cost;                        // Cost to buy the train
};

// GO class
class Go : public kindSquare
{
public:
    void process() const override;
};

// Jail class
class Jail : public kindSquare
{
public:
    Jail();
    void process() const override;

    int getTurnsInJail() const; // Returns the number of turns the player is in jail
    void incrementTurns();       // Increment the turns spent in jail

private:
    int turnsInJail; // Number of turns the player is in jail
};

// Special square classes
class Chance : public kindSquare
{
public:
    void process() const override;
};

class CommunityChest : public kindSquare
{
public:
    void process() const override;
};

class FreeParking : public kindSquare
{
public:
    void process() const override;
};

class Tax : public kindSquare
{
public:
    Tax(const std::string& name, int cost); // Constructor declaration
    void process() const override;

private:
    std::string name;                // Name of the Tax
    int cost;                        // Cost to pay
};

class GoToJail : public kindSquare
{
public:
    void process() const override;
};

class Utility : public kindSquare
{
public:
    Utility(const std::string& name, int cost); // Constructor declaration
    void process() const override;

private:
    std::string name;                // Name of the utility
    int cost;                        // Cost to buy the utility
};

#endif // KINDSQUARE_HPP
