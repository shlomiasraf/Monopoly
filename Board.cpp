#include "Board.hpp"

using namespace ariel;


std::vector<Square*> Board::Squares;

Board::Board() = default;

/**
 * @brief Creates the Monopoly board by initializing each square and storing them.
 * @param window The SFML window where the board will be displayed.
 */
void Board::createBoard(sf::RenderWindow& window)
{
    initializeKindSquare(window);
    int index = 0;
    while(index < 40)
    {
        Square* square = new Square(index, kinds[index],colors[index]);
        Squares.push_back(square); // Store the dynamically allocated Square's pointer
        index++;
    }
}

// Destructor
Board::~Board()
{
    // Clean up dynamic memory if you still use new elsewhere
    for (auto square : Squares)
    {
        delete square; // Assuming Squares is filled with dynamically allocated Square objects
    }
    for (kindSquare* kind : kinds)
    {
        delete kind;
    }
    kinds.clear();
}

/**
 * @brief Returns the vector of all the squares on the board.
 * @return A vector containing pointers to all squares on the board.
 */
std::vector<Square*> Board::getSquares()
{
    return Squares;
}

/**
 * @brief Initializes the types of squares and creates their graphical representations.
 * @param window The SFML window where the board will be displayed.
 */
void Board::initializeKindSquare(sf::RenderWindow &window)
{
    // Initialize kinds and create graphical squares
    kinds.push_back(new Go());
    createGraphicalSquare(0, "GO", sf::Color::White, window);
    colors.push_back("White");

    kinds.push_back(new Street("Mediterranean Avenue", 60, 54, 108, 97, 388, ColorGroup::Brown));
    createGraphicalSquare(1, "Mediter-\nranean\nAvenue\n$60", sf::Color(139, 69, 19), window); // Brown color
    colors.push_back("Brown");

    kinds.push_back(new CommunityChest());
    createGraphicalSquare(2, "Community\nChest", sf::Color(255, 192, 203), window);
    colors.push_back("Pink");

    kinds.push_back(new Street("Baltic Avenue", 60, 54, 108, 97, 388, ColorGroup::Brown));
    createGraphicalSquare(3, "Baltic\nAvenue\n$60", sf::Color(139, 69, 19), window); // Brown color
    colors.push_back("Brown");

    kinds.push_back(new Tax("Income Tax", 100));
    createGraphicalSquare(4, "Income\nTax\n$100", sf::Color::Red, window);
    colors.push_back("Red");

    kinds.push_back(new Train("Reading Railroad", 200));
    createGraphicalSquare(5, "Reading\nRailroad\n$200", sf::Color(211, 211, 211), window);
    colors.push_back("Gray");

    kinds.push_back(new Street("Oriental Avenue", 100, 90, 180, 162, 648, ColorGroup::LightBlue));
    createGraphicalSquare(6, "Oriental\nAvenue\n$100", sf::Color::Cyan, window);
    colors.push_back("Light Blue");

    kinds.push_back(new Chance());
    createGraphicalSquare(7, "Chance", sf::Color(255, 192, 203), window);
    colors.push_back("Pink");

    kinds.push_back(new Street("Vermont Avenue", 100, 90, 180, 162, 648, ColorGroup::LightBlue));
    createGraphicalSquare(8, "Vermont\nAvenue\n$100", sf::Color::Cyan, window);
    colors.push_back("Light Blue");

    kinds.push_back(new Street("Connecticut Avenue", 120, 108, 216, 194, 778, ColorGroup::LightBlue));
    createGraphicalSquare(9, "Connecticut\nAvenue\n$120", sf::Color::Cyan, window);
    colors.push_back("Light Blue");

    kinds.push_back(new Jail());
    createGraphicalSquare(10, "Jail", sf::Color::White, window);
    colors.push_back("White");

    kinds.push_back(new Street("St. Charles Place", 140, 126, 252, 227, 907, ColorGroup::Blue));
    createGraphicalSquare(11, "St. Charles\nPlace\n$140", sf::Color::Magenta, window);
    colors.push_back("Magenta");

    kinds.push_back(new Utility("Electric Company", 150));
    createGraphicalSquare(12, "Electric\nCompany\n$150", sf::Color(204, 153, 255), window);
    colors.push_back("Light Purple");

    kinds.push_back(new Street("States Avenue", 140, 126, 252, 227, 907, ColorGroup::Blue));
    createGraphicalSquare(13, "States\nAvenue\n$140", sf::Color::Magenta, window);
    colors.push_back("Magenta");

    kinds.push_back(new Street("Virginia Avenue", 160, 144, 288, 259, 1037, ColorGroup::Blue));
    createGraphicalSquare(14, "Virginia\nAvenue\n$160", sf::Color::Magenta, window);
    colors.push_back("Magenta");

    kinds.push_back(new Train("Pennsylvania Railroad", 200));
    createGraphicalSquare(15, "Pennsylvania\nRailroad\n$200", sf::Color(211, 211, 211), window);
    colors.push_back("Gray");

    kinds.push_back(new Street("St. James Place", 180, 162, 324, 292, 1166, ColorGroup::Orange));
    createGraphicalSquare(16, "St. James\nPlace\n$180", sf::Color(255, 165, 0), window); // Orange
    colors.push_back("Orange");

    kinds.push_back(new CommunityChest());
    createGraphicalSquare(17, "Community\nChest", sf::Color(255, 192, 203), window);
    colors.push_back("Pink");

    kinds.push_back(new Street("Tennessee Avenue", 180, 162, 324, 292, 1166, ColorGroup::Orange));
    createGraphicalSquare(18, "Tennessee\nAvenue\n$180", sf::Color(255, 165, 0), window); // Orange
    colors.push_back("Orange");

    kinds.push_back(new Street("New York Avenue", 200, 180, 360, 324, 1296, ColorGroup::Orange));
    createGraphicalSquare(19, "New York\nAvenue\n$200", sf::Color(255, 165, 0), window); // Orange
    colors.push_back("Orange");

    kinds.push_back(new FreeParking());
    createGraphicalSquare(20, "Free\nParking", sf::Color::White, window);
    colors.push_back("White");

    kinds.push_back(new Street("Kentucky Avenue", 220, 198, 396, 356, 1426, ColorGroup::Red));
    createGraphicalSquare(21, "Kentucky\nAvenue\n$220", sf::Color::Red, window);
    colors.push_back("Red");

    kinds.push_back(new Chance());
    createGraphicalSquare(22, "Chance", sf::Color(255, 192, 203), window);
    colors.push_back("Pink");

    kinds.push_back(new Street("Indiana Avenue", 220, 198, 396, 356, 1426, ColorGroup::Red));
    createGraphicalSquare(23, "Indiana\nAvenue\n$220", sf::Color::Red, window);
    colors.push_back("Red");

    kinds.push_back(new Street("Illinois Avenue", 240, 216, 432, 389, 1556, ColorGroup::Red));
    createGraphicalSquare(24, "Illinois\nAvenue\n$240", sf::Color::Red, window);
    colors.push_back("Red");

    kinds.push_back(new Train("B&O Railroad", 200));
    createGraphicalSquare(25, "B&O\nRailroad\n$200", sf::Color(211, 211, 211), window);
    colors.push_back("Gray");

    kinds.push_back(new Street("Atlantic Avenue", 260, 234, 468, 421, 1685, ColorGroup::Yellow));
    createGraphicalSquare(26, "Atlantic\nAvenue\n$260", sf::Color::Yellow, window);
    colors.push_back("Yellow");

    kinds.push_back(new Street("Ventnor Avenue", 260, 234, 468, 421, 1685, ColorGroup::Yellow));
    createGraphicalSquare(27, "Ventnor\nAvenue\n$260", sf::Color::Yellow, window);
    colors.push_back("Yellow");

    kinds.push_back(new Utility("Water Works", 150));
    createGraphicalSquare(28, "Water\nWorks\n$150", sf::Color(204, 153, 255), window);
    colors.push_back("Light Purple");

    kinds.push_back(new Street("Marvin Gardens", 280, 252, 504, 454, 1815, ColorGroup::Yellow));
    createGraphicalSquare(29, "Marvin\nGardens\n$280", sf::Color::Yellow, window);
    colors.push_back("Yellow");

    kinds.push_back(new GoToJail());
    createGraphicalSquare(30, "Go to\nJail", sf::Color::White, window);
    colors.push_back("White");

    kinds.push_back(new Street("Pacific Avenue", 300, 270, 540, 486, 1944, ColorGroup::Green));
    createGraphicalSquare(31, "Pacific\nAvenue\n$300", sf::Color::Green, window);
    colors.push_back("Green");

    kinds.push_back(new Street("North Carolina Avenue", 300, 270, 540, 486, 1944, ColorGroup::Green));
    createGraphicalSquare(32, "North\nCarolina\nAvenue\n$300", sf::Color::Green, window);
    colors.push_back("Green");

    kinds.push_back(new CommunityChest());
    createGraphicalSquare(33, "Community\nChest", sf::Color(255, 192, 203), window);
    colors.push_back("Pink");

    kinds.push_back(new Street("Pennsylvania Avenue", 320, 288, 576, 518, 2074, ColorGroup::Green));
    createGraphicalSquare(34, "Pennsy-\nlvania\nAvenue\n$320", sf::Color::Green, window);
    colors.push_back("Green");

    kinds.push_back(new Train("Short Line Railroad", 200));
    createGraphicalSquare(35, "Short Line\nRailroad\n$200", sf::Color(211, 211, 211), window);
    colors.push_back("Gray");

    kinds.push_back(new Chance());
    createGraphicalSquare(36, "Chance", sf::Color(255, 192, 203), window);
    colors.push_back("Pink");

    kinds.push_back(new Street("Park Place", 350, 315, 630, 567, 2268, ColorGroup::Blue));
    createGraphicalSquare(37, "Park\nPlace\n$350", sf::Color::Blue, window);
    colors.push_back("Blue");

    kinds.push_back(new Tax("Luxury Tax", 100));
    createGraphicalSquare(38, "Luxury\nTax\n$100", sf::Color::Red, window);
    colors.push_back("Red");

    kinds.push_back(new Street("Boardwalk", 400, 360, 720, 648, 2592, ColorGroup::Blue));
    createGraphicalSquare(39, "Boardwalk\n$400", sf::Color::Blue, window);
    colors.push_back("Blue");

    // After creating all squares, add title
    drawTitle(window);
}

/**
 * @brief Creates a graphical representation of a square on the board.
 * @param i The index of the square.
 * @param name The name displayed on the square.
 * @param color The color of the square.
 * @param window The SFML window where the square will be displayed.
 */
void Board::createGraphicalSquare(int i, const std::string &name, sf::Color color, sf::RenderWindow &window)
{
    const int BOARD_WIDTH = 800;
    const int BOARD_HEIGHT = 800;
    const double SQUARE_SIZE = 73; // Adjusted for 11 squares

    sf::RectangleShape squareShape(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    sf::Text squareText;

    // Load font for the text
    sf::Font font;
    font.loadFromFile("arial.ttf");

    // Set up the square text
    squareText.setFont(font);
    squareText.setString(name);
    squareText.setCharacterSize(12);
    squareText.setFillColor(sf::Color::Black);

    // Set the square's position based on its index (i)
    if (i < 11)
    {
        squareShape.setPosition(BOARD_WIDTH - (i + 1) * SQUARE_SIZE+3, BOARD_HEIGHT - SQUARE_SIZE);
    }
    else if (i < 20)
    {
        squareShape.setPosition(0, BOARD_HEIGHT - (i - 9) * SQUARE_SIZE);
    }
    else if (i < 31)
    {
        squareShape.setPosition((i - 20) * SQUARE_SIZE, 0);
    }
    else
    {
        squareShape.setPosition(BOARD_WIDTH - SQUARE_SIZE+3, (i - 30) * SQUARE_SIZE-2);
    }

    // Set the square's color
    squareShape.setFillColor(color);

    // Position text at the center of the square
    sf::FloatRect textRect = squareText.getLocalBounds();
    squareText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    squareText.setPosition(squareShape.getPosition().x + SQUARE_SIZE / 2, squareShape.getPosition().y + SQUARE_SIZE / 2);
    window.draw(squareShape);  // Draw the rectangle shape
    window.draw(squareText); // Draw the text on the square

    // Store the square and its text
    graphicalSquares.push_back(std::make_pair(squareShape, squareText));
}
/**
 * @brief Draws the title "Monopoly" at the center of the board.
 * @param window The SFML window where the title will be displayed.
 */
void Board::drawTitle(sf::RenderWindow &window)
{
    const int BOARD_WIDTH = 800;
    const int BOARD_HEIGHT = 800;
    const double SQUARE_SIZE = 73; // Adjusted for 11 squares
    sf::Font font;
    font.loadFromFile("arial.ttf"); // Load your font

    sf::Text title;
    title.setFont(font);
    title.setString("Monopoly");
    title.setCharacterSize(50); // Large text
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);

    // Center the text
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    title.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 - 50); // Adjust position

    window.draw(title);
    // Set up the roll dice button
    rollButton = Button(100, 50, "Roll Dice", font, sf::Color::Green, [](){});
    rollButton.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 10); // Adjust position
    rollButton.draw(window);

}
/**
 * @brief Adds a new square to the board based on user input.
 * @param window The SFML window where the new square will be displayed.
 */
void Board::addSquare(sf::RenderWindow& window)
{
    // Get the square kind from the user
    std::string kind;
    std::cout << "Enter the kind of the square: ";
    std::getline(std::cin, kind);

    // Get the square name from the user
    std::string name;
    std::cout << "Enter the name of the square: ";
    std::getline(std::cin, name);

    // Get the square color from the user
    std::string color;
    std::cout << "Enter the color of the square: ";
    std::getline(std::cin, color);

    // Get the index of the new square
    int i = Squares.size() - 1;
    // Create a new square object with the user's input

    Square* square = nullptr;
    // Create a map of string colors to sf::Color with 3 additional colors
    std::map<std::string, ColorGroup> colorMap = {
            {"blue", ColorGroup::Blue},
            {"green", ColorGroup::Green},
            {"yellow", ColorGroup::Yellow},
            {"orange", ColorGroup::Orange}, // Orange color
            {"pink",ColorGroup::Pink}, // Pink color
            {"lightblue", ColorGroup::LightBlue} // Added lightblue as an extra color
    };
    // Create a map of string colors to sf::Color with 3 additional colors
    std::map<std::string, sf::Color> colorMap2 = {
            {"blue", sf::Color::Blue},
            {"black", sf::Color::Black},
            {"green", sf::Color::Green},
            {"yellow", sf::Color::Yellow},
            {"purple", sf::Color(128, 0, 128)}, // Purple color
            {"orange", sf::Color(255, 165, 0)}, // Orange color
            {"pink", sf::Color(255, 192, 203)}, // Pink color
            {"cyan", sf::Color::Cyan} // Added cyan as an extra color
    };
    ColorGroup colorSquare;
    if(colorMap.find(color) != colorMap.end())
    {
        colorSquare = colorMap[color];
    }
    else
    {
        colorSquare = ColorGroup::Red;
    }
    // Determine the type of square based on the name and create the appropriate type
    if (kind == "Go")
    {
        kindSquare* kindSquare = new Go();
        Square* square = new Square(i, kindSquare,color);
    }
    else if (kind == "Chance")
    {
        kindSquare* kindSquare = new Chance();
        Square* square = new Square(i, kindSquare,color);
    }
    else if (kind == "Community Chest")
    {
        kindSquare* kindSquare = new CommunityChest();
        Square* square = new Square(i, kindSquare,color);
    }
    else if (kind == "Tax")
    {
        kindSquare* kindSquare = new Tax(name, 100);  // Tax square with specific amount
        Square* square = new Square(i, kindSquare,color);
    }
    else if (kind == "Utility")
    {
        kindSquare* kindSquare  = new Utility(name, 150);  // Utility square type
        Square* square = new Square(i, kindSquare,color);
    }
    else
    {
        kindSquare* kindSquare  = new Street(name, 60, 54, 108, 97, 388,colorSquare); // street square type
        Square* square = new Square(i, kindSquare,color);
    }
    // Add the new square to the internal storage
    Squares.push_back(square);

    // Create the graphical square and update the board

    if (colorMap2.find(color) != colorMap2.end())
    {
        createGraphicalSquare(i, name, colorMap2[color], window);
    }
    else
    {
        createGraphicalSquare(i, name, sf::Color::Red, window);
    }
}