#include <iostream>
#include "Button.hpp"

Button::Button() = default;

Button::Button(float width, float height, const std::string &label, sf::Font &font, const sf::Color &color, std::function<void()> action)
        : action(action)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // Center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(text);
}

void Button::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    text.setPosition(x + shape.getSize().x / 2, y + shape.getSize().y / 2);
}

bool Button::isMouseOver(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect bounds = shape.getGlobalBounds();
    return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool Button::isClicked(sf::RenderWindow &window)
{
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
