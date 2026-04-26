#include "Buttons.h"

// SALE BUTTON
// _________________________________________________________

// Public

Sale::Sale(Item* item, int amount, Properties properties, std::string text, std::string fontPath) :
	item(item), amount(amount), Button::Button(properties, text, fontPath) {};

Sale::~Sale() noexcept {
	if (item != nullptr) {
		item = nullptr;
		delete item;
	}
}

void Sale::Press() {
	item->Sale(amount);

	clickSound->play();
}



// REMOVE BUTTON
// _________________________________________________________

// Public

Remove::Remove(std::vector<Item*>& list, Item* item, Properties properties, std::string text, std::string fontPath) :
	list(list), item(item), Button(properties, text, fontPath) {
}

Remove::~Remove() noexcept {
	if (item != nullptr) {
		item = nullptr;
		delete item;
	}
}

void Remove::Press() {
	list.erase(std::remove(list.begin(), list.end(), item), list.end());
	item = nullptr;
	delete item;

	clickSound->play();
}



// ADD BUTTON
// _________________________________________________________

// Public

Add::Add(std::vector<Item*>& list, Properties properties, std::string text, std::string fontPath) :
	list(list), Button(properties, text, fontPath) {
	this->fontPath = fontPath;
}

void Add::Press() {
	Properties itemProps(properties.x, 0, 700, 60);
	Item* item = new Item(itemProps, 0, "", fontPath);

	Properties sellProps(0, 0, 40, 40, sf::Color(54, 176, 46));
	Properties unsellProps(0, 0, 40, 40, sf::Color(184, 48, 48));
	Properties removeProps(0, 0, 40, 40, sf::Color(184, 48, 48));
	Sale* sell = new Sale(item, 1, sellProps, "$", fontPath);
	Sale* unsell = new Sale(item, -1, unsellProps, "-$", fontPath);
	Remove* remove = new Remove(list, item, removeProps, "X", fontPath);
	item->SetButtons(sell, unsell, remove);

	Properties nameProps(0, 0, 300, 35, sf::Color::Blue);
	Properties priceProps(0, 0, 75, 35, sf::Color::Blue);
	TextBox* name = new TextBox(nameProps, "(click to edit)", "", fontPath);
	TextBox* price = new PriceBox(priceProps, "$0.00", "", fontPath);
	item->SetTextBoxes(name, price);

	list.push_back(item);

	clickSound->play();
}