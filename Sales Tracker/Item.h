#pragma once
#include <SFML/Graphics.hpp>
//#include "Button.h"
//#include "Buttons.h"

class Item
{
public:
    //Item(double price, std::string name, Sell* sell, Unsell* unsell, Remove* remove) : sell(sell), unsell(unsell), remove(remove) {
    //    properties.sold = 0;
    //    properties.price = price;
    //    properties.name = name;
    //}

    //Item(Item& other) {
    //    properties.sold = other.properties.sold;
    //    properties.price = other.properties.price;
    //    properties.name = other.properties.name;
    //    unsell = other.unsell;
    //    sell = other.sell;
    //}

    Item(float x = 0, float y = 0, float width = 0, float height = 0, sf::Color color = sf::Color::White, double price = 0, std::string name = "") : x(x), y(y), width(width), height(height), color(color) {
        properties.price = price;
        properties.name = name;
    }

    void Render(sf::RenderWindow& window) {
        sf::RectangleShape button({ width, height });
        button.setPosition({ x, y });
        button.setFillColor(color);
        window.draw(button);
    }

    void Sell() {
        properties.sold++;
    }

    void Unsell() {
        properties.sold--;
    }

private:
    float x, y;
    float width, height;
    sf::Color color;

    struct Properties {
        int sold = 0;
        double price = 0;
        std::string name = "";
    };
    Properties properties;

    //Button* sell = nullptr;
    //Button* unsell = nullptr;
    //Button* remove = nullptr;
};

