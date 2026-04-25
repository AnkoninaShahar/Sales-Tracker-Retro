#include "Item.h"

// Public

Item::Item(Properties properties, double price, std::string name, std::string font) :
    properties(properties)
{
    profile.price = price;
    profile.name = name;

    try {
        if (!this->font.openFromFile(font))
            throw "FAILED TO LOAD FONT:\t" + font;
    }
    catch(const char* msg) {
        std::cerr << msg << std::endl;
    }
}

Item::Item(const Item& other) {
    properties = other.properties;
    profile = other.profile;

    sell = other.sell;
    unsell = other.unsell;
    remove = other.remove;

    nameBox = other.nameBox;
    priceBox = other.priceBox;
}

Item::~Item() {
    if (sell != nullptr)
        delete sell;
    if (unsell != nullptr)
        delete unsell;
    if (remove != nullptr)
        delete remove;

    if (nameBox != nullptr)
        delete nameBox;
    if (priceBox != nullptr)
        delete priceBox;
}

bool Item::Interact(bool pressed, int mx, int my) {
    if (sell->IsPressed(pressed, mx, my))
        sell->Press();
    if (unsell->IsPressed(pressed, mx, my))
        unsell->Press();
    if (remove->IsPressed(pressed, mx, my)) {
        remove->Press();
        return true;
    }

    if (nameBox->IsPressed(pressed, mx, my))
        nameBox->Press();
    if (priceBox->IsPressed(pressed, mx, my))
        priceBox->Press();

    return false;
}

void Item::Edit(char character) {
    nameBox->Edit(character);
    priceBox->Edit(character);
}

void Item::EndEdit() {
    nameBox->ResetEditing();
    priceBox->ResetEditing();
}

void Item::Sale(int amount) {
    profile.sold += amount;
}

void Item::Render(sf::RenderWindow& window) {
    int olRed = properties.color.r * 0.35;
    int olGreen = properties.color.g * 0.35;
    int olBlue = properties.color.b * 0.35;

    sf::RectangleShape item({ properties.width, properties.height });
    item.setPosition({ properties.x, properties.y });
    item.setFillColor(sf::Color(194, 194, 194));
    item.setOutlineColor(sf::Color(olRed, olGreen, olBlue));
    item.setOutlineThickness(5);
    window.draw(item);


    sf::Text sold(font, "Sold " + std::to_string(profile.sold));
    sold.setCharacterSize(25);
    sold.setFillColor(sf::Color::Black);
    sold.setPosition({ properties.x + 535, properties.y + 12 });
    window.draw(sold);


    if (sell != nullptr)
        sell->Render(window);
    if (unsell != nullptr)
        unsell->Render(window);
    if (remove != nullptr)
        remove->Render(window);

    if (nameBox != nullptr)
        nameBox->Render(window);
    if (priceBox != nullptr)
        priceBox->Render(window);
}