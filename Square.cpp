#include "Square.hpp"

using namespace ariel;

// Default constructor
Square::Square() : kind(nullptr) {}

// Constructor with vertices and kindSquare
Square::Square(std::vector<Vertex> vertexs, kindSquare* kindSquareType)
        : Vertexs(vertexs), kind(kindSquareType) {}


// Getter for Vertexs
std::vector<Vertex> Square::getVertexs()
{
    return Vertexs;
}