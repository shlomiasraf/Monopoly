#ifndef KINDSQUARE_HPP
#define KINDSQUARE_HPP

#include <string>
#include <valarray>

namespace ariel
{
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
        virtual int process(int money) const = 0; // Pure virtual function for specific behavior of different square types
    };

    // Street class
    class Street : public kindSquare {
    public:
        Street(const std::string &name, int price, int rent, int houseCost, int rentWithHouse, int rentWithHotel,
               ColorGroup colorGroup);
        ~Street() = default;
        int process(int) const override; // Pass Player by reference
        int buildHouse(int,int);
        int buyStreet(int);
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
    class Train : public kindSquare {
    public:
        Train(const std::string &name, int cost); // Constructor declaration
        ~Train() = default;
        int process(int numOfTrains) const override; // Pass Player by reference
        int buyTrain(int money);
    private:
        std::string name;                // Name of the train
        int cost;                        // Cost to buy the train
    };

    // GO class
    class Go : public kindSquare {
    public:
        ~Go() = default;
        int process(int money) const override; // Pass Player by reference
    };

    // Jail class
    class Jail : public kindSquare {
    public:
        ~Jail() = default;
        int process(int money) const override; // Pass Player by reference
    };

    // Special square classes
    class Chance : public kindSquare {
    public:
        ~Chance() = default;
        int process(int money) const override; // Pass Player by reference
    };

    class CommunityChest : public kindSquare {
    public:
        ~CommunityChest() = default;
        int process(int money) const override; // Pass Player by reference
    };

    class FreeParking : public kindSquare {
    public:
        ~FreeParking() = default;
        int process(int money) const override; // Pass Player by reference
    };

    class Tax : public kindSquare {
    public:
        ~Tax() = default;
        Tax(const std::string &name, int cost); // Constructor declaration
        int process(int money) const override; // Pass Player by reference

    private:
        std::string name;                // Name of the tax
        int cost;                        // Cost to pay
    };

    class GoToJail : public kindSquare {
    public:
        ~GoToJail() = default;
        int process(int money) const override; // Pass Player by reference
    };

    class Utility : public kindSquare {
    public:
        ~Utility() = default;
        Utility(const std::string &name, int cost); // Constructor declaration
        int process(int money) const override; // Pass Player by reference
        int buyUtility(int money);
    private:
        std::string name;                // Name of the utility
        int cost;                        // Cost to buy the utility
    };
}
#endif // KINDSQUARE_HPP