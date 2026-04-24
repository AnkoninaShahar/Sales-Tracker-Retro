#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

#include "Button.h"
#include "TextBox.h"
#include "Helper.h"

using namespace Helper;

class Item
{
public:
    Item(Properties properties = Properties(), double price = 0, std::string name = "", std::string font = "Fonts\\Thraex.ttf");
    Item(const Item& other);
    ~Item();

    bool Interact(bool pressed, int mx, int my);

    void Edit(char character);
    void EndEdit();

    void Sale(int amount);

    void Render(sf::RenderWindow& window);

    void SetButtons(Button* sell, Button* unsell, Button* remove) {
        this->sell = sell;
        this->unsell = unsell;
        this->remove = remove;
    }

    void SetTextBoxes(TextBox* name, TextBox* price) {
        this->nameBox = name;
        this->priceBox = price;
    }

    void SetPosition(float x, float y) {
        properties.x = x;
        properties.y = y;

        if (sell != nullptr)
            sell->SetPosition(x + 5, y + 5);
        if (unsell != nullptr)
            unsell->SetPosition(x + 55, y + 5);
        if (remove != nullptr)
            remove->SetPosition(x + 640, y + 5);

        if (nameBox != nullptr)
            nameBox->SetPosition(x + 150, y + 5);
        if (priceBox != nullptr)
            priceBox->SetPosition(x + 300, y + 5);
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

    sf::Font font;

    Button* sell = nullptr;
    Button* unsell = nullptr;
    Button* remove = nullptr;

    TextBox* nameBox = nullptr;
    TextBox* priceBox = nullptr;
};

