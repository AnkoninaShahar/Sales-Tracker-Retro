#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Helper.h"

using namespace Helper;

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

    Item(Properties properties, double price = 0, std::string name = "") : properties(properties)
    {
        statistics.price = price;
        statistics.name = name;
    }

    void Render(sf::RenderWindow& window) {
        sf::RectangleShape button({ properties.width, properties.height });
        button.setPosition({ properties.x, properties.y });
        button.setFillColor(properties.color);
        window.draw(button);
    }

    void Sell() {
        statistics.sold++;
    }

    void Unsell() {
        statistics.sold--;
    }

private:
    struct Statistics {
        int sold = 0;
        double price = 0;
        std::string name = "";
    };
    Statistics statistics;
    Properties properties;

    Button* sell = nullptr;
    Button* unsell = nullptr;
    Button* remove = nullptr;
};

