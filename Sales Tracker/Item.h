#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

#include "Button.h"
#include "Helper.h"

using namespace Helper;

class Item
{
public:
    Item(Properties properties = Properties(), double price = 0, std::string name = "") :
        properties(properties) {
        profile.price = price;
        profile.name = name;
    }

    Item(const Item& other) {
        properties = other.properties;
        profile = other.profile;

        sell = other.sell;
        unsell = other.unsell;
        remove = other.remove;
    }

    void Interact(bool pressed, int mx, int my) {
        if (sell->IsPressed(pressed, mx, my))
            sell->Press();
        if (unsell->IsPressed(pressed, mx, my))
            unsell->Press();
        if (remove->IsPressed(pressed, mx, my))
            remove->Press();
    }

    void Render(sf::RenderWindow& window) {
        sf::RectangleShape item({ properties.width, properties.height });
        item.setPosition({ properties.x, properties.y });
        item.setFillColor(properties.color);
        window.draw(item);

        sf::Font font;
        if (font.openFromFile("Fonts\\Thraex.ttf")) {
            sf::Text text(font, profile.name);
            text.setCharacterSize(30);
            text.setFillColor(sf::Color::Black);
            text.setPosition({ properties.x + 150, properties.y + 5 });

            sf::Text price(font, "$" + std::to_string(profile.price));
            price.setCharacterSize(30);
            price.setFillColor(sf::Color::Black);
            price.setPosition({ properties.x + 300, properties.y + 5 });

            sf::Text sold(font, "Sold " + std::to_string(profile.sold));
            sold.setCharacterSize(30);
            sold.setFillColor(sf::Color::Black);
            sold.setPosition({ properties.x + 500, properties.y + 5 });

            window.draw(text);
            window.draw(price);
            window.draw(sold);
        }

        if (sell != nullptr)
            sell->Render(window);
        if (unsell != nullptr)
            unsell->Render(window);
        if (remove != nullptr)
            remove->Render(window);
    }

    void Sell() {
        profile.sold++;
    }

    void Unsell() {
        profile.sold--;
    }

    void SetButtons(Button* sell, Button* unsell, Button* remove) {
        this->sell = sell;
        this->unsell = unsell;
        this->remove = remove;
    }

    void SetPosition(float x, float y) {
        properties.x = x;
        properties.y = y;

        if (sell != nullptr)
            sell->SetPosition(properties.x + 5, properties.y + 5);
        if (unsell != nullptr)
            unsell->SetPosition(properties.x + 55, properties.y + 5);
        if (remove != nullptr)
            remove->SetPosition(properties.x + 640, properties.y + 5);
    }

    bool operator==(const Item& other) const {
        std::cout << this << "\t" << &other << std::endl;
        return this == &other;
    }
    

private:
    struct Profile {
        int sold = 0;
        double price = 0;
        std::string name = "";
    };
    Profile profile;
    Properties properties;

    Button* sell = nullptr;
    Button* unsell = nullptr;
    Button* remove = nullptr;
};

