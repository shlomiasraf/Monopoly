#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Square.hpp"
#include "kindSquare.hpp"
#include "Button.hpp"

namespace ariel
{
    class Board
    {
    private:
        static std::vector<Square*> Squares;                   // Stores all squares on the board
        std::vector<kindSquare*> kinds;                       // Stores various kinds of squares (Street, Go, Jail, etc.)
        std::vector<std::string> colors;
        std::vector<std::pair<sf::RectangleShape, sf::Text>> graphicalSquares;  // Stores the graphical representation of squares
    public:
        Button rollButton;
        Board();
        void createBoard(sf::RenderWindow& window);           // Function to create and display the board
        void initializeKindSquare(sf::RenderWindow& window);  // Function to initialize the squares and their graphical representations
        void createGraphicalSquare(int i, const std::string& name, sf::Color color, sf::RenderWindow &);  // Function to create and position graphical squares
        void drawTitle(sf::RenderWindow &window);             // Function to draw the title "Monopoly"
        static std::vector<Square*> getSquares();              // Getter for the squares on the board
    };
}

#endif // BOARD_HPP
