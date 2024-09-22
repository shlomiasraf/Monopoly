#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "Vertex.hpp"
#include <vector>
#include "kindSquare.hpp"

namespace ariel
{
    class Board;
    class Square
    {
    private:
        std::vector<Vertex> Vertexs;
        kindSquare* kind; // Pointer to base class to support polymorphism
    public:
        Square();
        Square(std::vector<Vertex> vertices, kindSquare* kind);
        std::vector<Vertex> getVertexs();
    };
}
#endif //SQUARE_HPP
