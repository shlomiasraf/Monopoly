#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button
{
private:
    sf::RectangleShape shape;    // Shape of the button
    sf::Text text;              // Text displayed on the button
    std::function<void()> action; // Function to be called on button click

public:
    Button(float width, float height, const std::string &label, sf::Font &font, const sf::Color &color, std::function<void()> action);

    void draw(sf::RenderWindow &window);
    void setPosition(float x, float y);
    bool isMouseOver(sf::RenderWindow &window);
    bool isClicked(sf::RenderWindow &window);
};

#endif // BUTTON_HPP
