#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Item.h"
#include "Button.h"
#include "Buttons.h"
#include "Helper.h"
#include "ScrollBar.h"

using namespace Helper; // Namespace for helper functions and structs

/// <summary>
/// Manages a collection of items and handles rendering, scrolling, and item editing for an SFML render window.
/// </summary>
class ScreenManager
{
public:
	ScreenManager(); // Constructor
	~ScreenManager() noexcept; // Destructor

	/// <summary>
	/// Scrolls the view or contents of the specified SFML render window by the given offset.
	/// </summary>
	/// <param name="scroll">Amount to scroll (positive or negative offset). The exact units or interpretation (pixels, lines, etc.) depend on the implementation.</param>
	/// <param name="window">Reference to the sf::RenderWindow whose view or contents will be scrolled or adjusted.</param>
	void Scroll(float scroll, sf::RenderWindow& window);

	/// <summary>
	/// Edits an item using the specified character.
	/// </summary>
	/// <param name="character">The character used to specify the edit for the item.</param>
	void EditItem(char character);

	/// <summary>
	/// Renders graphical content to the provided sf::RenderWindow.
	/// </summary>
	/// <param name="window">Reference to the sf::RenderWindow that will be used as the rendering target. The window may be modified by drawing operations.</param>
	void Render(sf::RenderWindow& window);

private:
	std::vector<Item*> items; // List of items being managed
	Add add; // Button for adding new items
	ScrollBar bar; // Scroll bar for navigating through items

	// Variables for managing scrolling behavior
	sf::View scrollView;
	float scroll, prevScroll;
	int scrollTime = 0;
	bool scrollEdge = false;

	// Resources
	sf::Font font;
	sf::Texture logo;

	void RenderBackground(sf::RenderWindow& window) const; // Renders the background elements of the screen
	void RenderUI(sf::Vector2i mousePos, sf::RenderWindow& window); // Renders the user interface elements, potentially using the mouse position for interaction

	void RenderBorder(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Color color, int thickness) const; // Renders a border with specified properties
	void RenderIndentBorder(sf::RenderWindow& window, sf::FloatRect rect, int indent) const; // Renders an indented border based on a rectangle and indent value
	void RenderTitle(sf::RenderWindow& window) const; // Renders the title of the screen
	void RenderSprite(sf::RenderWindow& window, sf::Texture texture, sf::Vector2f position, sf::Vector2f scale) const; // Renders a sprite with the given texture, position, and scale


	bool MouseInScrollWindow(sf::Vector2i mousePos, sf::RenderWindow& window) const; // Checks if the mouse position is within the scrollable area of the window
	void CorrectScroll(); // Adjusts the scroll position to ensure it stays within valid bounds, potentially based on the number of items and the size of the scrollable area
};

