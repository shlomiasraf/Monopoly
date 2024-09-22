#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <string>
#include <unordered_map>

namespace ariel
{
    class Vertex
    {
    private:
        int x;
        int y;
        static std::unordered_map<std::string, Vertex> vertexMap;

    public:
        Vertex();
        Vertex(int,int);
        int getX();
        int getY();
        static Vertex& createVertex(int,int);
        static Vertex& getVertex(int,int);
        std::vector<Vertex*> getNeighborsVertex();
        bool operator==(Vertex);
    };
}

#endif // VERTEX_HPP
