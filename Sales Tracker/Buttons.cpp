#include "Buttons.h"

// SALE BUTTON
// _________________________________________________________

// Public

Sale::Sale(Item* item, int amount, Properties properties, std::string text, std::string font) :
	item(item), amount(amount), Button::Button(properties, text, font) {};

Sale::~Sale() {
	if (item != nullptr) {
		item = nullptr;
		delete item;
	}
}

void Sale::Press() {
	item->Sale(amount);
}



// REMOVE BUTTON
// _________________________________________________________

// Public

Remove::Remove(std::vector<Item*>& list, Item* item, Properties properties, std::string text, std::string font) :
	list(list), item(item), Button(properties, text, font) {
}

Remove::~Remove() {
	if (item != nullptr) {
		item = nullptr;
		delete item;
	}
}

void Remove::Press() {
	list.erase(std::remove(list.begin(), list.end(), item), list.end());
	item = nullptr;
	delete item;
}



// ADD BUTTON
// _________________________________________________________

// Public

Add::Add(std::vector<Item*>& list, Properties properties, std::string text, std::string font) :
	list(list), Button(properties, text, font) {
}

void Add::Press() {
	Properties itemProps(properties.x, 0, 700, 60);

	Properties sellProps(5, 5, 50, 50, sf::Color::Green);
	Properties unsellProps(55, 5, 50, 50, sf::Color::Red);
	Properties removeProps(640, 5, 50, 50, sf::Color::Red);

	Properties nameProps(0, 0, 100, 50, sf::Color::Blue);
	Properties priceProps(0, 0, 100, 50, sf::Color::Blue);

	Item* blank = new Item(itemProps);

	Sale* sell = new Sale(blank, 1, sellProps);
	Sale* unsell = new Sale(blank, -1, unsellProps);
	Remove* remove = new Remove(list, blank, removeProps);
	blank->SetButtons(sell, unsell, remove);

	TextBox* name = new TextBox(nameProps, "Blank");
	TextBox* price = new TextBox(priceProps, "$0.00");
	blank->SetTextBoxes(name, price);

	list.push_back(blank);
}