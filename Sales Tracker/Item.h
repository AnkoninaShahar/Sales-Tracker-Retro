#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

#include "Button.h"
#include "TextBox.h"
#include "Helper.h"

using namespace Helper; // Namespace for helper functions and structs

/// <summary>
/// Represents a UI item that stores visual/layout properties, a sales profile, and associated controls. Manages rendering, user interaction, and basic editing/sales operations.
/// </summary>
class Item
{
public:
	Item(Properties properties = Properties(), double price = 0, std::string name = "", std::string fontPath = "Assets\\Fonts\\Thraex.ttf"); // Constructor with default parameters for properties, price, name, and font path
	Item(const Item& other) noexcept; // Copy constructor that initializes a new Item as a copy of an existing one; performs deep copying of resources and member variables to ensure independent operation of the new instance
	~Item() noexcept; // Destructor that releases any resources owned by the Item instance, such as dynamically allocated memory or SFML resources, to prevent memory leaks and ensure proper cleanup when an Item object goes out of scope or is deleted

    /// <summary>
    /// Processes an interaction event at the specified coordinates and indicates whether the event was handled.
    /// </summary>
    /// <param name="pressed">True if the input is in a pressed/active state (e.g., a mouse button is down), false if released.</param>
    /// <param name="mx">X coordinate of the interaction position.</param>
    /// <param name="my">Y coordinate of the interaction position.</param>
    /// <returns>True if the item is to be removed, false otherwise.</returns>
    bool Interact(bool pressed, int mx, int my);

    /// <summary>
    /// Performs an edit operation using the specified character.
    /// </summary>
    /// <param name="character">The character to use for the edit operation.</param>
    void Edit(char character);

    /// <summary>
    /// Processes a sale for the specified amount.
    /// </summary>
    /// <param name="amount">The amount associated with the sale.</param>
    void Sale(int amount);

    /// <summary>
    /// Renders graphical content to the provided SFML render window.
    /// </summary>
    /// <param name="window">Reference to the sf::RenderWindow to draw into. The function issues draw calls and updates the window's contents.</param>
    void Render(sf::RenderWindow& window);

    /// <summary>
    /// Sets the object's sell, unsell, and remove button members to the provided pointers.
    /// </summary>
    /// <param name="sell">Pointer to the Button to assign to the object's sell member.</param>
    /// <param name="unsell">Pointer to the Button to assign to the object's unsell member.</param>
    /// <param name="remove">Pointer to the Button to assign to the object's remove member.</param>
    void SetButtons(Button* sell, Button* unsell, Button* remove) {
        this->sell = sell;
        this->unsell = unsell;
        this->remove = remove;
    }

    /// <summary>
    /// Assigns the provided TextBox pointers to the object's nameBox and priceBox members.
    /// </summary>
    /// <param name="name">Pointer to a TextBox to assign to the object's nameBox member.</param>
    /// <param name="price">Pointer to a TextBox to assign to the object's priceBox member.</param>
    void SetTextBoxes(TextBox* name, TextBox* price) {
        this->nameBox = name;
        this->priceBox = price;
    }

    /// <summary>
    /// Sets the object's position and updates positions of its child controls using fixed offsets.
    /// </summary>
    /// <param name="x">The new X coordinate for the object (horizontal position).</param>
    /// <param name="y">The new Y coordinate for the object (vertical position).</param>
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

    /// <summary>
    /// Computes the total value by multiplying profile.sold by profile.price. This is a const member function and does not modify the object.
    /// </summary>
    /// <returns>The total as a double (profile.sold * profile.price).</returns>
    double GetTotal() const {
        return profile.sold * profile.price;
    }

    /// <summary>
    /// Prints the object's information without modifying it (const member function).
    /// </summary>
    void Print() const;

    /// <summary>
    /// Checks whether this Item and another Item are the same instance by comparing their addresses. The function prints the addresses of both objects to std::cout as a side effect.
    /// </summary>
    /// <param name="other">The other Item to compare (const reference).</param>
    /// <returns>true if both refer to the same object (address equality, i.e., identity); otherwise false.</returns>
    bool operator==(const Item& other) const {
        std::cout << this << "\t" << &other << std::endl;
        return this == &other;
    }

    /// <summary>
    /// Inserts the textual representation of an Item into the output stream, followed by a newline (std::endl).
    /// </summary>
    /// <param name="os">The output stream to write to; receives the formatted Item.</param>
    /// <param name="item">The Item to be formatted and written, passed as a const reference.</param>
    /// <returns>A reference to the output stream (os) after the insertion.</returns>
    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        return os << item.ToString() << std::endl;
    }

private:
	// Struct to hold the sales profile information for the item, including name, price, and quantity sold. This struct is used as a member variable to encapsulate related data about the item's sales performance.
    struct Profile {
        std::string name = "";
        double price = 0;
        int sold = 0;
    };
    Profile profile;
    Properties properties;

	sf::Font font; // Font resource used for rendering text related to the item; this member variable holds the font data and is initialized in the constructor, allowing the Item to render its name, price, or other text using this font.

	// Button pointers for the item's controls; these may be set to point to actual Button instances that perform actions related to selling, unselling, or removing the item. The Item class manages these pointers and uses them to position the buttons relative to the item's properties.
    Button* sell = nullptr;
    Button* unsell = nullptr;
    Button* remove = nullptr;

	// TextBox pointers for the item's name and price input fields; these may be set to point to actual TextBox instances that allow the user to edit the item's name and price. The Item class manages these pointers and uses them to position the text boxes relative to the item's properties.
    TextBox* nameBox = nullptr;
    TextBox* priceBox = nullptr;

	std::string ToString() const; // Private helper function that generates a string representation of the Item, including its name, price, quantity sold, and total value. This function is used by the Print() method and the stream insertion operator to provide a formatted description of the Item's state.
};

