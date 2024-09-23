

#include "Player.hpp"

using namespace ariel;

const int BOARD_WIDTH = 800;
const int BOARD_HEIGHT = 800;
const double SQUARE_SIZE = 73; // Adjusted for 11 squares
const float TOKEN_RADIUS = 10.0f; // Adjust size as needed
// Create a map of string colors to sf::Color with 3 additional colors
std::map<std::string, sf::Color> colorMap = {
        {"blue", sf::Color::Blue},
        {"black", sf::Color::Black},
        {"green", sf::Color::Green},
        {"yellow", sf::Color::Yellow},
        {"purple", sf::Color(128, 0, 128)}, // Purple color
        {"orange", sf::Color(255, 165, 0)}, // Orange color
        {"pink", sf::Color(255, 192, 203)}, // Pink color
        {"cyan", sf::Color::Cyan} // Added cyan as an extra color
};
Player::Player(std::string name,std::string color,sf::RenderWindow &window,int serialNum): currentSquare(Board::getSquares()[0])
{
    this->name = name;
    this->color = color;
    this->money = 1500;
    this->currentIndex = 0;
    this->serialNum = serialNum;
    initializePlayerToken(window);
}
std::string Player::getColor()
{
    return this->color;
}
std::string Player::getName()
{
    return this->name;
}
void Player::printMoney()
{
    std::cout<< "the total money of " << this->name << " with color " << this->color << " is: " << this->money << "\n";
}

// New function to draw the purchase button on the screen
void Player::drawBuyButton(sf::RenderWindow &window)
{
    // Load font for the text
    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Set up the roll dice button
    buyButton = Button(100, 50, "yes", font, sf::Color::Yellow, [](){});
    buyButton.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 240); // Adjust position
    buyButton.draw(window);
}

bool Player::handleBuyButtonClick(sf::RenderWindow &window)
{
    if(currentSquare->ownerColor == "None" || checkIfCanBuildHouse())
    {
        int moneyAfter;
        if(currentSquare->ownerColor == "None")
        {
            moneyAfter = currentSquare->getKind()->process(money);
        }
        else
        {
            Street* street = dynamic_cast<Street*>(currentSquare);
            moneyAfter = street->buildHouse(money,currentSquare->numberOfHouses);
            if(moneyAfter > 0)
            {
                currentSquare->numberOfHouses++;
            }
        }
        if(moneyAfter > 0)
        {
            sizeMarkers++;
            sf::CircleShape newMarker(5.0f); // Create a small circle for ownership
            newMarker.setFillColor(token.getFillColor()); // Set the marker's color to match the player's token color
            // Adjust the position of the marker (near the player's token)
            newMarker.setPosition(token.getPosition().x + 15, token.getPosition().y + 15);
            // Add the new marker to the ownershipMarkers vector
            ownershipMarkers.push_back(newMarker);
            money = moneyAfter;
            ownedProperties.push_back(*currentSquare);
            // For example, drawing a small circle on the square to indicate ownership
            currentSquare->ownerColor = color;
            nowBuy = true;
            return true;
        }
    }
    return false;
}
void Player::initializePlayerToken(sf::RenderWindow &window)
{
    int i = this->serialNum;
    token.setRadius(TOKEN_RADIUS); // Set the radius of the token
    // Find the color based on the player's color string
    if (colorMap.find(color) != colorMap.end())
    {
        token.setFillColor(colorMap[color]); // Set the token color
    }
    else
    {
        token.setFillColor(sf::Color::Red); // Default to white if color not found
    }
    token.setPosition(BOARD_WIDTH  - (SQUARE_SIZE/1.5) , BOARD_HEIGHT - (SQUARE_SIZE)+12*(i+1)-10); // Adjust positioning
    // Load font for the text
    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Initialize the text for player name and money
    playerInfo.setFont(font); // Set the font
    playerInfo.setCharacterSize(14); // Text size
    playerInfo.setFillColor(colorMap[color]); // Text color same as token
    playerInfo.setString(name + ": $" + std::to_string(money)); // Set the string (name and money)
    // Update the player info (name and money) position and string
    playerInfo.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 35*(i+1));
    playerInfo.setString(name + ": $" + std::to_string(money));
    window.draw(token);
    window.draw(playerInfo);

}

Square* Player::getCurrentSquare()
{
    return currentSquare;
}
void Player::drawTokenAndInfo(sf::RenderWindow &window)
{
    window.draw(token);
    // Load font for the text
    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Initialize the text for player name and money
    playerInfo.setFont(font); // Set the font
    playerInfo.setCharacterSize(14); // Text size
    playerInfo.setString(name + ": $" + std::to_string(money)); // Set the string (name and money)
    // Update the player info (name and money) position and string
    playerInfo.setFillColor(colorMap[color]); // Text color same as token
    playerInfo.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 35*(serialNum+1));
    playerInfo.setString(name + ": $" + std::to_string(money));
    window.draw(playerInfo);
    for(int i = 0; i < sizeMarkers; i++)
    {
        window.draw(ownershipMarkers[i]); // Draw the marker on the window
    }
    // Check if the current square is purchasable
    if (currentSquare->isPurchasable() && !nowBuy && hisTurn && ((currentSquare->ownerColor == color && checkIfCanBuildHouse()) || currentSquare->ownerColor == "None"))  // Dummy function to check if the square can be bought
    {
        if(currentSquare->ownerColor == "None")
        {
            playerInfo.setString("do you want to buy the property?");
        }
        else
        {
            playerInfo.setString("do you want to buy a house?");
        }
        playerInfo.setPosition(BOARD_WIDTH / 2 - 100, BOARD_HEIGHT / 2 + 200);
        playerInfo.setFillColor(sf::Color::Black);
        window.draw(playerInfo);
        drawBuyButton(window); // Draw the button to buy the property
    }
}
void Player::setCurrentSquare(int numToMove ,sf::RenderWindow &window)
{
    int i = this->serialNum;
    if(currentIndex+numToMove >= Board::getSquares().size())
    {
        this->currentSquare = Board::getSquares()[currentIndex+numToMove-Board::getSquares().size()];
        currentIndex = currentIndex+numToMove-Board::getSquares().size();
    }
    else
    {
        this->currentSquare = Board::getSquares()[currentIndex+numToMove];
        currentIndex += numToMove;
    }
    // Set the square's position based on its index (i)
    if (currentIndex < 11)
    {
        token.setPosition(BOARD_WIDTH +10- (currentIndex + 1) * SQUARE_SIZE+3, BOARD_HEIGHT +10- SQUARE_SIZE+5*(i+1));
    }
    else if (currentIndex < 20)
    {
        token.setPosition(20, BOARD_HEIGHT - (currentIndex - 9) * SQUARE_SIZE+5*(i+1));
    }
    else if (currentIndex < 31)
    {
        token.setPosition((currentIndex - 20) * SQUARE_SIZE+10, 5*(i+1));
    }
    else
    {
        token.setPosition(BOARD_WIDTH - SQUARE_SIZE+3, (currentIndex- 30) * SQUARE_SIZE+5*(i+1));
    }
    if (currentSquare->isPurchasable())  // Dummy function to check if the square can be bought
    {
        if(currentSquare->ownerColor == "None" || checkIfCanBuildHouse())
        {
            drawBuyButton(window); // Draw the button to buy the property
            nowBuy = false;
        }
    }
}

bool Player::checkIfCanBuildHouse()
{
    std::string  color2 = currentSquare->ownerColor;
    std::string  kind = currentSquare->getKindAsString();
    if(currentSquare->ownerColor == color && currentSquare->getKindAsString() == "Street")
    {
        for(int i = currentSquare->getIndex()+1; i < currentSquare->getIndex()+4 && i < Board::getSquares().size(); i++)
        {
            if(Board::getSquares()[i]->getColor() == currentSquare->getColor())
            {
                if(Board::getSquares()[i]->ownerColor != color)
                {
                    return false;
                }
            }
        }
        for(int i = currentSquare->getIndex()-1; i > currentSquare->getIndex()-4 && i > 0; i--)
        {
            if(Board::getSquares()[i]->getColor() == currentSquare->getColor())
            {
                if(Board::getSquares()[i]->ownerColor != color)
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
