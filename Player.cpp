

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
/**
 * @brief Constructor for the Player class.
 * @param name The name of the player.
 * @param color The color of the player's token.
 * @param window The reference to the render window for drawing.
 * @param serialNum The player's serial number for positioning.
 */
Player::Player(std::string name,std::string color,sf::RenderWindow &window,int serialNum): currentSquare(Board::getSquares()[0])
{
    this->name = name;
    this->color = color;
    this->money = 1500;
    this->currentIndex = 0;
    this->serialNum = serialNum;
    initializePlayerToken(window);
}
/**
 * @brief Get the player's color.
 * @return The color of the player as a string.
 */
std::string Player::getColor()
{
    return this->color;
}

/**
 * @brief Get the player's name.
 * @return The name of the player as a string.
 */
std::string Player::getName()
{
    return this->name;
}

/**
 * @brief Draw the buy button on the screen.
 * @param window The reference to the render window for drawing.
 */
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
/**
 * @brief Handle the buy button click event.
 * @param window The reference to the render window for drawing.
 * @return True if the purchase was successful, false otherwise.
 */
bool Player::handleBuyButtonClick(sf::RenderWindow &window)
{
    if(currentSquare->ownerColor == "None" || checkIfCanBuildHouse() || checkIfCanBuildHotel())
    {
        int moneyAfter;
        if(currentSquare->ownerColor == "None")
        {
            if(getCurrentSquare()->getKindAsString() == "Street")
            {
                Street *street = dynamic_cast<Street *>(currentSquare->getKind());
                moneyAfter = street->buyStreet(money);
            }
            else if(getCurrentSquare()->getKindAsString() == "Train")
            {
                Train *train = dynamic_cast<Train *>(currentSquare->getKind());
                moneyAfter = train->buyTrain(money);
                if(moneyAfter > 0)
                {
                    numberOfTrains++;
                }
            }
            else
            {
                Utility *utility = dynamic_cast<Utility *>(currentSquare->getKind());
                moneyAfter = utility->buyUtility(money);
            }
            if (moneyAfter > 0)
            {
                sizeMarkers++;
                sf::CircleShape newMarker(5.0f); // Create a small circle for ownership
                newMarker.setFillColor(token.getFillColor()); // Set the marker's color to match the player's token color
                // Adjust the position of the marker (near the player's token)
                newMarker.setPosition(token.getPosition().x + 15, token.getPosition().y + 15);
                // Add the new marker to the ownershipMarkers vector
                ownershipMarkers.push_back(newMarker);
            }
        }
        else
        {
            Street* street = dynamic_cast<Street*>(currentSquare->getKind());
            moneyAfter = street->buildHouse(money, currentSquare->numberOfHouses);
            if (moneyAfter > 0)
            {
                currentSquare->numberOfHouses++;
                sizeMarkers++;
                sf::CircleShape newMarker(6.0f); // Create a small circle for ownership
                newMarker.setFillColor(token.getFillColor()); // Set the marker's color to match the player's token color
                // Adjust the position of the marker (near the player's token)
                newMarker.setPosition(token.getPosition().x+10*(currentSquare->numberOfHouses), token.getPosition().y-3*(currentSquare->numberOfHouses));
                // Add the new marker to the ownershipMarkers vector
                if(currentSquare->numberOfHouses == 5)
                {
                    newMarker.setRadius(10.0f); // Create a small circle for ownership
                    newMarker.setPosition(token.getPosition().x, token.getPosition().y);

                }
                ownershipMarkers.push_back(newMarker);
            }
        }
        if(moneyAfter > 0)
        {
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
/**
 * @brief Initialize the player's token and information on the screen.
 * @param window The reference to the render window for drawing.
 */
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
    playerInfo.setFillColor(token.getFillColor()); // Text color same as token
    playerInfo.setString(name + ": $" + std::to_string(money)); // Set the string (name and money)
    // Update the player info (name and money) position and string
    playerInfo.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 35*(i+1));
    playerInfo.setString(name + ": $" + std::to_string(money));
    window.draw(token);
    window.draw(playerInfo);

}
/**
 * @brief Get the current square the player is on.
 * @return Pointer to the current square.
 */
Square* Player::getCurrentSquare()
{
    return currentSquare;
}

/**
 * @brief Draw the player's token, information, and ownership markers.
 * @param window The reference to the render window for drawing.
 */

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
    playerInfo.setFillColor(token.getFillColor()); // Text color same as token
    playerInfo.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 35*(serialNum+1));
    playerInfo.setString(name + ": $" + std::to_string(money));
    window.draw(playerInfo);
    for(int i = 0; i < sizeMarkers; i++)
    {
        window.draw(ownershipMarkers[i]); // Draw the marker on the window
    }
    // Check if the current square is purchasable
    if (currentSquare->isPurchasable() && !nowBuy && hisTurn && ((currentSquare->ownerColor == color && (checkIfCanBuildHouse() || checkIfCanBuildHotel())) || currentSquare->ownerColor == "None"))  // Dummy function to check if the square can be bought
    {
        if(currentSquare->ownerColor == "None")
        {
            playerInfo.setString("do you want to buy the property?");
        }
        else
        {
            if(currentSquare->numberOfHouses < 4)
            {
                playerInfo.setString("do you want to buy a house?");
            }
            if(currentSquare->numberOfHouses == 4)
            {
                playerInfo.setString("do you want to buy a hotel?");
            }
        }
        playerInfo.setPosition(BOARD_WIDTH / 2 - 100, BOARD_HEIGHT / 2 + 200);
        playerInfo.setFillColor(sf::Color::Black);
        window.draw(playerInfo);
        drawBuyButton(window); // Draw the button to buy the property
    }
}
/**
 * @brief Set the current square the player is on.
 * @param square Pointer to the new current square.
 */
void Player::setCurrentSquare(int numToMove ,sf::RenderWindow &window)
{
    int i = this->serialNum;
    if(currentIndex+numToMove >= Board::getSquares().size())
    {
        money += 200;
        std::cout << name << " passed Go and received 200!" << std::endl;
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
        if(currentSquare->ownerColor == "None" || checkIfCanBuildHouse() || checkIfCanBuildHotel())
        {
            drawBuyButton(window); // Draw the button to buy the property
            nowBuy = false;
        }
    }
}

/**
 * @brief Check if the player can build a house on their current square.
 * @return True if the player can build a house, false otherwise.
 */
bool Player::checkIfCanBuildHouse()
{
    if(currentSquare->ownerColor == color && currentSquare->getKindAsString() == "Street" && currentSquare->numberOfHouses < 4)
    {
        for(int i = currentSquare->getIndex()+1; i < currentSquare->getIndex()+4 && i < Board::getSquares().size(); i++)
        {
            if(Board::getSquares()[i]->getColor() == currentSquare->getColor())
            {
                if(Board::getSquares()[i]->ownerColor != color || Board::getSquares()[i]->numberOfHouses < currentSquare->numberOfHouses)
                {
                    return false;
                }
            }
        }
        for(int i = currentSquare->getIndex()-1; i > currentSquare->getIndex()-4 && i > 0; i--)
        {
            if(Board::getSquares()[i]->getColor() == currentSquare->getColor())
            {
                if(Board::getSquares()[i]->ownerColor != color || Board::getSquares()[i]->numberOfHouses < currentSquare->numberOfHouses)
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
/**
 * @brief Check if the player can build a hotel on their current square.
 * @return True if the player can build a hotel, false otherwise.
 */
bool Player::checkIfCanBuildHotel()
{
    if(currentSquare->ownerColor == color && currentSquare->getKindAsString() == "Street" && currentSquare->numberOfHouses == 4)
    {
        return true;
    }
    return false;
}