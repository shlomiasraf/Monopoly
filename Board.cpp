
#include "Board.hpp"

using namespace ariel;

Board::Board() = default;
std::vector<Square> Board::Squares;

void Board::createBoard()
{
    initializeKindSquare();
    int j = 0;
    int i = 0;
    int index = 0;
    while(i < 10)
    {
        createSquare(Vertex(i,j),kinds[index]);
        i++;
        index++;
    }
    while(j < 10)
    {
        createSquare(Vertex(i,j),kinds[index]);
        j++;
        index++;
    }
    while (i > 0)
    {
        createSquare(Vertex(i,j),kinds[index]);
        i--;
        index++;
    }
    while (j > 0)
    {
        createSquare(Vertex(i,j),kinds[i]);
        j--;
        index++;
    }
    sf::RenderWindow window(sf::VideoMode(800, 800), "Monopoly Board");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Call a method to draw the board
        draw(window);
        window.display();
}
void Board::draw(sf::RenderWindow& window)
{
    for (auto& square : Squares)
`   {
        square.draw(window);
    }
}
void Board::createSquare(Vertex v,kindSquare* kind)
{
    // Get or create the flyweight vertex
    Vertex& v1 = Vertex::createVertex(v.getX(),v.getY());
    // Get or create the flyweight vertices for v2 to v4
    Vertex& v2 = Vertex::createVertex(v1.getX() + 1, v1.getY());
    Vertex& v3 = Vertex::createVertex(v1.getX(), v1.getY() + 1);
    Vertex& v4 = Vertex::createVertex(v1.getX() + 1, v1.getY()+1);

    // Create the vector of vertices
    std::vector<Vertex> vertexs = {v1, v2, v3, v4};

    // Create the hexagon and add it to the board
    Squares.push_back(Square(vertexs, kind));
}
std::vector<Square> Board::getSquares()
{
    return Squares;
}
void Board::initializeKindSquare()
{
    // Initialize kinds with the appropriate objects
    kinds.push_back(new Go()); // GO square

    // Properties on the board
    kinds.push_back(new Street("Mediterranean Avenue", 60, 54, 108, 97, 388, (ColorGroup::Brown)));
    kinds.push_back(new CommunityChest()); // Community Chest square
    kinds.push_back(new Street("Baltic Avenue", 60, 54, 108, 97, 388, (ColorGroup::Brown)));
    kinds.push_back(new Tax("Income Tax", 200)); // Income Tax, flat 200 M
    kinds.push_back(new Train("Reading Railroad", 200)); // Reading Railroad
    kinds.push_back(new Street("Oriental Avenue", 100, 90, 180, 162, 648, (ColorGroup::LightBlue)));
    kinds.push_back(new Chance()); // Chance square
    kinds.push_back(new Street("Vermont Avenue", 100, 90, 180, 162, 648, (ColorGroup::LightBlue)));
    kinds.push_back(new Street("Connecticut Avenue", 120, 108, 216, 194, 778, (ColorGroup::LightBlue)));
    kinds.push_back(new Jail()); // Jail square
    kinds.push_back(new Street("St. Charles Place", 140, 126, 252, 227, 907, (ColorGroup::Pink)));
    kinds.push_back(new Utility("Electric Company", 150)); // Electric Company
    kinds.push_back(new Street("States Avenue", 140, 126, 252, 227, 907, (ColorGroup::Pink)));
    kinds.push_back(new Street("Virginia Avenue", 160, 144, 288, 259, 1037, (ColorGroup::Pink)));
    kinds.push_back(new CommunityChest()); // Community Chest square
    kinds.push_back(new Train("Pennsylvania Railroad", 200)); // Pennsylvania Railroad
    kinds.push_back(new Street("St. James Place", 180, 162, 324, 292, 1166, (ColorGroup::Orange)));
    kinds.push_back(new Chance()); // Chance square
    kinds.push_back(new Street("Tennessee Avenue", 180, 162, 324, 292, 1166, (ColorGroup::Orange)));
    kinds.push_back(new Street("New York Avenue", 200, 180, 360, 324, 1296, (ColorGroup::Orange)));
    kinds.push_back(new FreeParking()); // Free Parking square
    kinds.push_back(new Street("Kentucky Avenue", 220, 198, 396, 356, 1426, (ColorGroup::Red)));
    kinds.push_back(new Chance()); // Chance square
    kinds.push_back(new Street("Indiana Avenue", 220, 198, 396, 356, 1426, (ColorGroup::Red)));
    kinds.push_back(new Street("Illinois Avenue", 240, 216, 432, 389, 1556, (ColorGroup::Red)));
    kinds.push_back(new Train("B&O Railroad", 200)); // B&O Railroad
    kinds.push_back(new Street("Atlantic Avenue", 260, 234, 468, 421, 1685, (ColorGroup::Yellow)));
    kinds.push_back(new Street("Ventnor Avenue", 260, 234, 468, 421, 1685, (ColorGroup::Yellow)));
    kinds.push_back(new Utility("Water Works", 150)); // Water Works
    kinds.push_back(new Street("Marvin Gardens", 280, 252, 504, 454, 1815, (ColorGroup::Yellow)));
    kinds.push_back(new GoToJail()); // Go to Jail square
    kinds.push_back(new Street("Pacific Avenue", 300, 270, 540, 486, 1944, (ColorGroup::Green)));
    kinds.push_back(new CommunityChest()); // Community Chest square
    kinds.push_back(new Street("North Carolina Avenue", 300, 270, 540, 486, 1944, (ColorGroup::Green)));
    kinds.push_back(new Chance()); // Chance square
    kinds.push_back(new Street("Pennsylvania Avenue", 320, 288, 576, 518, 2074, (ColorGroup::Green)));
    kinds.push_back(new Train("Short Line Railroad", 200)); // Short Line Railroad
    kinds.push_back(new Street("Park Place", 350, 315, 630, 567, 2268, (ColorGroup::Blue)));
    kinds.push_back(new Tax("Luxury Tax", 100)); // Luxury Tax, flat 100 M
    kinds.push_back(new Street("Boardwalk", 400, 360, 720, 648, 2592, (ColorGroup::Blue)));
}
