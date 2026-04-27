#pragma once
#include "Button.h"

/// <summary>
/// An editable text input control derived from Button. Supports placeholder (empty) text, initial content, font selection, keyboard sound effects, and rendering via SFML.
/// </summary>
class TextBox : public Button
{
public:
	TextBox(Properties properties = Properties(), std::string empty = "", std::string text = "", std::string font = "Assets\\Fonts\\Thraex.ttf"); // Constructor with default parameters for properties, empty text, initial text, and font path
	~TextBox() noexcept; // Destructor

	/// <summary>
	/// Handles the press event for the text box.
	/// </summary>
	void Press() noexcept override;

	/// <summary>
	/// Handles the mouse button press event.
	/// </summary>
	/// <param name="pressed">Indicates whether the button is pressed.</param>
	/// <param name="mx">The mouse x-coordinate.</param>
	/// <param name="my">The mouse y-coordinate.</param>
	/// <returns>True if the button is pressed; otherwise, false.</returns>
	bool IsPressed(bool pressed, int mx, int my) override;

	/// <summary>
	/// Handles character input for the text box.
	/// </summary>
	/// <param name="character">The character to add to the text box.</param>
	virtual void Edit(char character);

	/// <summary>
	/// Renders the text box.
	/// </summary>
	/// <param name="window">The render window.</param>
	virtual void Render(sf::RenderWindow& window) override;

private:
	bool editing = false; // Indicates whether the text box is currently being edited
	std::string empty; // Placeholder text to display when the text box is empty

	// Sound buffers and sound objects for keyboard input feedback
	sf::SoundBuffer keyboardBuffers[5];
	sf::Sound* keyboardSounds[5];
};


/// <summary>
/// A specialized text box for entering prices.
/// </summary>
class PriceBox : public TextBox
{
public:
	using TextBox::TextBox; // Inherit constructors from TextBox

	/// <summary>
	/// Handles character input for the price box.
	/// </summary>
	/// <param name="character">The character to add to the price box.</param>
	void Edit(char character) override;

	/// <summary>
	/// Renders the price box.
	/// </summary>
	/// <param name="window">The render window.</param>
	void Render(sf::RenderWindow& window) override;

private:
	float price = 0.0f; // The current price value represented by the text box
	std::string fText = ""; // Formatted text to display the price with a currency symbol
};

