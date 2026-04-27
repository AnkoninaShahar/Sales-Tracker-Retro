#include "Buttons.h"

// SALE BUTTON
// _________________________________________________________

// Public

Sale::Sale(Item* item, int amount, Properties properties, std::string text, std::string fontPath) :
	item(item), amount(amount), Button::Button(properties, text, fontPath) {};

Sale::~Sale() noexcept {
	// Clean up the associated Item pointer if it is not null to prevent memory leaks.
	if (item != nullptr) {
		item = nullptr;
		delete item;
	}
}

void Sale::Press() noexcept {
	item->Sale(amount);	// Call the Sale method on the associated Item object with the specified amount to process the sale. 
	clickSound->play(); // Play a click sound effect to provide feedback for the interaction.
}



// REMOVE BUTTON
// _________________________________________________________

// Public

Remove::Remove(std::vector<Item*>& list, Item* item, Properties properties, std::string text, std::string fontPath) :
	list(list), item(item), Button(properties, text, fontPath) {
}

Remove::~Remove() noexcept {
	// Clean up the associated Item pointer if it is not null to prevent memory leaks.
	if (item != nullptr) {
		item = nullptr;
		delete item;
	}
}

void Remove::Press() noexcept {
	list.erase(std::remove(list.begin(), list.end(), item), list.end()); // Remove the associated Item pointer from the list of items using the erase-remove idiom. This effectively removes the item from the list while maintaining the integrity of the vector. 
	
	// Clean up the associated Item pointer after removing it from the list to prevent memory leaks. Set the pointer to null before deleting it to avoid dangling pointers.
	item = nullptr;
	delete item;

	clickSound->play(); // Play a click sound effect to provide feedback for the interaction.
}



// ADD BUTTON
// _________________________________________________________

// Public

Add::Add(std::vector<Item*>& list, Properties properties, std::string text, std::string fontPath) :
	list(list), Button(properties, text, fontPath) {
	// Store the provided font path in the Add button's member variable for later use when creating new items. 
	this->fontPath = fontPath;
}

void Add::Press() noexcept {
	// Create a new Item with specified properties, price, name, and font path. 
	Properties itemProps(properties.x, 0, 700, 60);
	Item* item = new Item(itemProps, 0, "", fontPath);

	// Set up the sell, unsell, and remove buttons for the new item with specific properties and colors.
	Properties sellProps(0, 0, 40, 40, sf::Color(54, 176, 46));
	Properties unsellProps(0, 0, 40, 40, sf::Color(184, 48, 48));
	Properties removeProps(0, 0, 40, 40, sf::Color(184, 48, 48));
	Sale* sell = new Sale(item, 1, sellProps, "$", fontPath);
	Sale* unsell = new Sale(item, -1, unsellProps, "-$", fontPath);
	Remove* remove = new Remove(list, item, removeProps, "X", fontPath);
	item->SetButtons(sell, unsell, remove);

	// Set up the name and price text boxes for the new item with specific properties and colors.
	Properties nameProps(0, 0, 300, 35, sf::Color::Blue);
	Properties priceProps(0, 0, 75, 35, sf::Color::Blue);
	TextBox* name = new TextBox(nameProps, "(click to edit)", "", fontPath);
	TextBox* price = new PriceBox(priceProps, "$0.00", "", fontPath);
	item->SetTextBoxes(name, price);

	// Add the newly created item to the list of items and play a click sound effect to provide feedback for the interaction.
	list.push_back(item);
	clickSound->play();
}