#include "Item.h"

// Public

Item::Item(Properties properties, double price, std::string name, std::string fontPath) :
    properties(properties)
{
    profile.price = price;
    profile.name = name;

    try {
        if (!font.openFromFile(fontPath))
            throw "FAILED TO LOAD FONT:\t" + fontPath;
    }
    catch(const char* msg) {
        std::cerr << msg << std::endl;
    }
}

Item::Item(const Item& other) noexcept {
    properties = other.properties;
    profile = other.profile;

    sell = other.sell;
    unsell = other.unsell;
    remove = other.remove;

    nameBox = other.nameBox;
    priceBox = other.priceBox;
}

Item::~Item() noexcept {
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
    if (nameBox != nullptr) {
        nameBox->Edit(character);
        profile.name = nameBox->GetText();
    }

    if (priceBox != nullptr) {
        priceBox->Edit(character);
        if (priceBox->GetText().size() > 0 && std::isdigit(priceBox->GetText()[0]))
            profile.price = std::stod(priceBox->GetText());
        else
            profile.price = 0;
    }
}

void Item::EndEdit() {
    nameBox->ResetEditing();
    priceBox->ResetEditing();
}

void Item::Sale(int amount) {
    profile.sold += amount;
}

void Item::Render(sf::RenderWindow& window) {
    int ol[3] = { properties.color.r * 0.35, properties.color.g * 0.35, properties.color.b * 0.35 };

    sf::RectangleShape item({ properties.width, properties.height });
    item.setPosition({ properties.x, properties.y });
    item.setFillColor(sf::Color(194, 194, 194));
    item.setOutlineColor(sf::Color(ol[0], ol[1], ol[2]));
    item.setOutlineThickness(5);
    window.draw(item);

    sf::Text sold(font, "Sold " + std::to_string(profile.sold));
    sold.setCharacterSize(30);
    sold.setFillColor(sf::Color::Black);
    sold.setPosition({ properties.x + 545, properties.y + 12 });
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

void Item::Print() const {
    std::cout << ToString() << std::endl;
}

// Private

std::string Item::ToString() const {
    std::string className = typeid(*this).name();
    std::string title = "===================================================================================================\n\n" +
        className +
        "\n---------------";
    std::string name = "NAME: " + profile.name + "\t";
    std::string price = std::format("PRICE: ${0:.2f}\t", profile.price);
    std::string sold = std::format("SOLD: {0}\t", profile.sold);
    std::string total = std::format("TOTAL: ${0:.2f}\t", GetTotal());
    std::string position = std::format("POSITION [x, y]: ( {0:.2f}, {1:.2f} )\t", properties.x, properties.y);
    std::string size = std::format("SIZE [width x height]: {0:.2f} x {1:.2f}\t", properties.width, properties.height);
    std::string color = std::format("COLOR [r, g, b]: ( {0}, {1}, {2} )\t", properties.color.r, properties.color.g, properties.color.b);
    std::string end = "===================================================================================================";
    return title + "\n\n" + name + price + sold + total + "\n\n" + position + size + color + "\n\n" + end + "\n";
}