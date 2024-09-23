#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "kindSquare.hpp"

namespace ariel
{
    class Square
    {
    private:
        kindSquare* kind; // Pointer to base class to support polymorphism
        int index;
        std::string color;

    public:
        virtual ~Square() {} // Add a virtual destructor
        int numberOfHouses = 0;
        std::string ownerColor = "None";
        Square();
        Square(int index, kindSquare* kind,std::string color);
        std::string getColor();
        int getIndex();
        kindSquare* getKind();
        bool isPurchasable();
        std::string getKindAsString();
    };
}
#endif //SQUARE_HPP
