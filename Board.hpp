
#ifndef BOARD_HPP
#define BOARD_HPP
#include "Square.hpp"
#include "kindSquare.hpp"
#include <SFML/Graphics.hpp>

namespace ariel
{
    class Board
    {
        private:
            static std::vector<Square> Squares;
            std::vector<kindSquare*> kinds;
        public:
            Board();
            void createBoard();
            void initializeKindSquare();
            void draw(sf::RenderWindow& window);
            void createSquare(Vertex, kindSquare*);
            static std::vector<Square> getSquares();
    };
}



#endif //BOARD_HPP
