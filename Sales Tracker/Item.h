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
    Item(Properties properties = Properties(), double price = 0, std::string name = "", std::string fontPath = "Fonts\\Thraex.ttf");
    Item(const Item& other) noexcept;
    ~Item() noexcept;

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
            sell->SetPosition(x + 10, y + 10);
        if (unsell != nullptr)
            unsell->SetPosition(x + 65, y + 10);
        if (remove != nullptr)
            remove->SetPosition(x + 645, y + 10);

        if (nameBox != nullptr)
            nameBox->SetPosition(x + 125, y + 12);
        if (priceBox != nullptr)
            priceBox->SetPosition(x + 445, y + 12);
    }

    double GetTotal() const {
        return profile.sold * profile.price;
    }

    void Print() const;

    bool operator==(const Item& other) const {
        std::cout << this << "\t" << &other << std::endl;
        return this == &other;
    }

    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        return os << item.ToString() << std::endl;
    }

private:
    struct Profile {
        std::string name = "";
        double price = 0;
        int sold = 0;
    };
    Profile profile;
    Properties properties;

    sf::Font font;

    Button* sell = nullptr;
    Button* unsell = nullptr;
    Button* remove = nullptr;

    TextBox* nameBox = nullptr;
    TextBox* priceBox = nullptr;

    std::string ToString() const;
};

