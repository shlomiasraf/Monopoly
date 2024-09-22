#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Square.hpp"
#include "kindSquare.hpp"
#include "Button.hpp"
#include "Player.hpp"
#include "Monopoly.hpp"

namespace ariel
{
    class Board
    {
    private:
        static std::vector<Square> Squares;                   // Stores all squares on the board
        std::vector<kindSquare*> kinds;                       // Stores various kinds of squares (Street, Go, Jail, etc.)
        std::vector<std::pair<sf::RectangleShape, sf::Text>> graphicalSquares;  // Stores the graphical representation of squares
        std::vector<sf::CircleShape> playerTokens;           // Stores player tokens

    public:
        bool roolDice = false;
        Board();
        void createBoard();                                   // Function to create and display the board
        void initializeKindSquare(sf::RenderWindow& window);  // Function to initialize the squares and their graphical representations
        void createSquares();
        void createSquare(Vertex v, kindSquare* kind);        // Function to create a square on the board based on position and kind
        void createGraphicalSquare(int i, const std::string& name, sf::Color color, sf::RenderWindow &);  // Function to create and position graphical squares
        void initializePlayerTokens(sf::RenderWindow &window); // Function to initialize player tokens
        void drawTitle(sf::RenderWindow &window);             // Function to draw the title "Monopoly"
        static std::vector<Square> getSquares();              // Getter for the squares on the board
    };
}

#endif // BOARD_HPP
