#pragma once
#include <vector>

#include "Button.h"
#include "TextBox.h"
#include "Item.h"

/// <summary>
/// Represents a Sale button UI element associated with an Item; when pressed it performs the sale action.
/// </summary>
class Sale : public Button
{
public:
	Sale(Item* item = nullptr, int amount = 0, Properties properties = Properties(), std::string text = "", std::string fontPath = "Assets\\Fonts\\Thraex.ttf"); // Constructor with default parameters for item, amount, properties, text, and font path
	~Sale() noexcept; // Destructor

	/// <summary>
	/// Performs the object's press action; overrides a virtual method from the base class.
	/// </summary>
	void Press() noexcept override;

private:
	Item* item; // Pointer to the associated Item object; may be nullptr if not set
	int amount; // The amount to be sold when the button is pressed; its interpretation depends on the context of the Item's sale method
};


/// <summary>
/// A Button subclass that removes an Item pointer from a provided list when pressed.
/// </summary>
class Remove : public Button
{
public:
	Remove(std::vector<Item*>& list, Item* item = nullptr, Properties properties = Properties(), std::string text = "", std::string fontPath = "Assets\\Fonts\\Thraex.ttf"); // Constructor with default parameters for list, item, properties, text, and font path
	~Remove() noexcept; // Destructor

	/// <summary>
	/// Performs the object's press action, overriding the base class Press() implementation.
	/// </summary>
	void Press() noexcept override;

private:
	std::vector<Item*>& list; // Reference to a vector of Item pointers; this list will be modified by the Press() method to remove the associated item
	Item* item; // Pointer to the Item that should be removed from the list when the button is pressed; may be nullptr if not set
};


/// <summary>
/// A Button-derived control bound to a vector of Item pointers. Represents an "Add" button that, when pressed, performs the add action on the associated list.
/// </summary>
class Add : public Button
{
public:
	Add(std::vector<Item*>& list, Properties properties = Properties(), std::string text = "", std::string fontPath = "Assets\\Fonts\\Thraex.ttf"); // Constructor with default parameters for list, properties, text, and font path

	/// <summary>
	/// Overrides a base class Press() method to perform a press action.
	/// </summary>
	void Press() noexcept override;

private:
	std::vector<Item*>& list; // Reference to a vector of Item pointers; this list will be modified by the Press() method to add a new item
	std::string fontPath; // The file path to the font used for the button's text; this may be used in the Press() method when creating new items or for other purposes related to the button's functionality
};
