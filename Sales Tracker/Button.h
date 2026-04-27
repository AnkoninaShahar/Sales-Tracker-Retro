#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <typeinfo>

#include "Helper.h"

using namespace Helper; // Namespace for helper functions and structs

/// <summary>
/// Abstract base class representing an interactive UI button. Provides position/size/text management, rendering, and input-handling interfaces for derived button types.
/// </summary>
class Button
{
public:
	Button(Properties properties = Properties(), std::string text = "", std::string fontPath = "Assets\\Fonts\\Thraex.ttf"); // Constructor with default parameters for properties, text, and font path
	Button(const Button& other) noexcept; // Copy constructor
	virtual ~Button() noexcept; // Virtual destructor for proper cleanup of derived classes

	/// <summary>
	/// Pure virtual member function representing a press action; it has no implementation and must be overridden by derived classes.
	/// </summary>
	virtual void Press() noexcept = 0;

	/// <summary>
	/// Determines whether the element is considered pressed based on the current pressed state and mouse position.
	/// </summary>
	/// <param name="pressed">A boolean flag indicating whether the input (for example, a mouse button) is currently pressed.</param>
	/// <param name="mx">The x-coordinate of the mouse cursor (integer).</param>
	/// <param name="my">The y-coordinate of the mouse cursor (integer).</param>
	/// <returns>true if the element should be considered pressed given the provided pressed flag and mouse coordinates; otherwise false.</returns>
	virtual bool IsPressed(bool pressed, int mx, int my);

	/// <summary>
	/// Determines whether the specified mouse coordinates are hovering over this object.
	/// </summary>
	/// <param name="mx">The x-coordinate of the mouse or cursor.</param>
	/// <param name="my">The y-coordinate of the mouse or cursor.</param>
	/// <returns>true if the point (mx, my) is considered to be hovering over the object; otherwise false.</returns>
	virtual bool IsHovering(int mx, int my) const;

	/// <summary>
	/// Virtual method that moves the object by the specified x (horizontal) and y (vertical) offsets. Can be overridden in derived classes.
	/// </summary>
	/// <param name="x">Horizontal offset or x-coordinate used for the movement.</param>
	/// <param name="y">Vertical offset or y-coordinate used for the movement.</param>
	virtual void Move(float x, float y);

	/// <summary>
	/// Virtual member function that renders the object to the provided sf::RenderWindow. Derived classes should override this to implement custom drawing.
	/// </summary>
	/// <param name="window">Reference to the sf::RenderWindow used as the target for drawing.</param>
	virtual void Render(sf::RenderWindow& window);

	/// <summary>
	/// Virtual method that sets the object's position by updating internal properties.x and properties.y.
	/// </summary>
	/// <param name="x">The new X coordinate.</param>
	/// <param name="y">The new Y coordinate.</param>
	virtual void SetPosition(float x, float y) {
		properties.x = x;
		properties.y = y;
	}

	/// <summary>
	/// Sets the object's width and height to the specified values.
	/// </summary>
	/// <param name="width">The new width to assign to the object.</param>
	/// <param name="height">The new height to assign to the object.</param>
	virtual void SetSize(float width, float height) {
		properties.width = width;
		properties.height = height;
	}
	
	/// <summary>
	/// Sets the object's text member to the provided string. This virtual method can be overridden by derived classes.
	/// </summary>
	/// <param name="text">The new text to assign to the object. Passed by value (copied).</param>
	virtual void SetText(std::string text) {
		this->text = text;
	}

	/// <summary>
	/// Returns the object's position as an sf::Vector2f.
	/// </summary>
	/// <returns>An sf::Vector2f containing the x and y coordinates from the object's properties (returned by value).</returns>
	virtual sf::Vector2f GetPosition() const {
		return sf::Vector2f(properties.x, properties.y);
	}

	/// <summary>
	/// Returns the object's size as an sf::Vector2f containing width and height.
	/// </summary>
	/// <returns>An sf::Vector2f where x is properties.width (width) and y is properties.height (height).</returns>
	virtual sf::Vector2f GetSize() const {
		return sf::Vector2f(properties.width, properties.height);
	}

	/// <summary>
	/// Virtual, const-qualified member function that returns the object's stored text.
	/// </summary>
	/// <returns>A std::string containing the value of the member variable 'text' (returned by value).</returns>
	virtual std::string GetText() const {
		return text;
	}

	/// <summary>
	/// Prints a representation of the object. This method is virtual and marked const, so it can be overridden by derived classes and does not modify the object's state.
	/// </summary>
	virtual void Print() const;

	/// <summary>
	/// Stream insertion operator that writes a Button's string representation to the output stream, appends a newline, and flushes the stream.
	/// </summary>
	/// <param name="os">The output stream to write to; it will be modified and returned.</param>
	/// <param name="button">The Button to be written as text (passed by const reference).</param>
	/// <returns>A reference to the same std::ostream after writing the button text and flushing, enabling chaining.</returns>
	friend std::ostream& operator<<(std::ostream& os, const Button& button) {
		return os << button.ToString() << std::endl;
	}

protected:
	// Member variables
	Properties properties;
	std::string text;

	// Resources
	sf::Font font;
	sf::SoundBuffer clickBuffer;
	sf::Sound* clickSound;

	// State variables
	enum ButtonState {
		NONE,
		HOVER,
		PRESSED
	};
	ButtonState status;

	bool mousePressed; // Tracks whether the mouse button is currently pressed

	virtual std::string ToString() const; // Converts the button's state to a string representation for printing
};

