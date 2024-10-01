#include <iostream>
#include "Button.hpp"

/**
 * @brief Default constructor for the Button class.
 *
 * Initializes the button with default values.
 */
Button::Button() = default;

/**
 * @brief Parameterized constructor for the Button class.
 *
 * Creates a button with the specified dimensions, label, font, color, and action.
 * The text is centered within the button shape.
 *
 * @param width Width of the button.
 * @param height Height of the button.
 * @param label Text label displayed on the button.
 * @param font Font used to render the button's text.
 * @param color Fill color of the button.
 * @param action Function to execute when the button is clicked.
 */
Button::Button(float width, float height, const std::string &label, sf::Font &font, const sf::Color &color, std::function<void()> action)
        : action(action)
{
    // Set the size and color of the button shape
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);

    // Set the text properties (font, string, size, color)
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);  // Set font size
    text.setFillColor(sf::Color::Black);  // Text color

    // Center the text within the button
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

/**
 * @brief Draws the button (shape and text) to the specified window.
 *
 * @param window Reference to the SFML window where the button will be rendered.
 */
void Button::draw(sf::RenderWindow &window)
{
    // Draw the button shape
    window.draw(shape);

    // Draw the button label text
    window.draw(text);
}

/**
 * @brief Sets the position of the button on the window.
 *
 * Moves the button shape and centers the text accordingly.
 *
 * @param x X-coordinate of the button's new position.
 * @param y Y-coordinate of the button's new position.
 */
void Button::setPosition(float x, float y)
{
    // Set the button's position
    shape.setPosition(x, y);

    // Center the text relative to the button's shape
    text.setPosition(x + shape.getSize().x / 2, y + shape.getSize().y / 2);
}

/**
 * @brief Checks if the mouse cursor is hovering over the button.
 *
 * Determines if the mouse position is within the bounds of the button.
 *
 * @param window Reference to the SFML window where the button is displayed.
 * @return true if the mouse is over the button; false otherwise.
 */
bool Button::isMouseOver(sf::RenderWindow &window)
{
    // Get the mouse position relative to the window
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Get the bounds of the button's shape
    sf::FloatRect bounds = shape.getGlobalBounds();

    // Check if the mouse position is inside the button's bounds
    return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

/**
 * @brief Checks if the button has been clicked.
 *
 * The button is considered clicked if the left mouse button is pressed
 * while the cursor is hovering over the button.
 *
 * @param window Reference to the SFML window where the button is displayed.
 * @return true if the button is clicked; false otherwise.
 */
bool Button::isClicked(sf::RenderWindow &window)
{
    // Check if the mouse is over the button and the left mouse button is pressed
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
