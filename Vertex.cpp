
#include "Vertex.hpp"

using namespace ariel;
std::unordered_map<std::string, Vertex> Vertex::vertexMap;
#include <iostream>

Vertex::Vertex() = default;

Vertex::Vertex(int x, int y)
{
    this->x = x;
    this->y = y;
}
Vertex &Vertex::createVertex(int x, int y)
{
    // Create a string key by concatenating x and y values
    std::string key = std::to_string(x) + "," + std::to_string(y);

    // Check if the vertex already exists in the map
    auto it = vertexMap.find(key);
    if (it != vertexMap.end())
    {
        // Vertex already exists, return the existing instance
        return it->second;
    }
    // Create a new vertex and store it in the map
    Vertex newVertex(x, y);
    vertexMap[key] = newVertex;
    return vertexMap[key];
}

Vertex& Vertex::getVertex(int x, int y)
{
    // Create a string key by concatenating x and y values
    std::string key = std::to_string(x) + "," + std::to_string(y);

    // Check if the vertex already exists in the map
    auto it = vertexMap.find(key);
    if (it != vertexMap.end())
    {
        // Vertex already exists, return the existing instance
        return it->second;
    }
    throw std::out_of_range("this vertex " +key +" isn't on the board.");
}


int Vertex::getX() 
{
    return this->x;
}

int Vertex::getY() 
{
    return this->y;
}

bool Vertex::operator==(Vertex other)
{
    return this->x == other.getX() && this->y == other.getY();
}
