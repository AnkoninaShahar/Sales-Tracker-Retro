#pragma once
#include "Button.h"

/// <summary>
/// A ScrollBar UI control (derived from Button) that manages a draggable thumb (bar) inside a track and provides methods to move, render, and query the scroll position.
/// </summary>
class ScrollBar : public Button
{
public:
	ScrollBar(Properties track = Properties(), Properties bar = Properties(), std::string text = ""); // Constructor with default parameters for track properties, bar properties, and text

	/// <summary>
	/// Executes the press action; overrides the base-class virtual implementation.
	/// </summary>
	void Press() noexcept override;

	/// <summary>
	/// Overrides base class method to determine whether the element is pressed based on the given pressed state and mouse coordinates.
	/// </summary>
	/// <param name="pressed">Boolean indicating whether the input (e.g., mouse button) is currently pressed.</param>
	/// <param name="mx">The x-coordinate of the mouse or pointer.</param>
	/// <param name="my">The y-coordinate of the mouse or pointer.</param>
	/// <returns>True if the element is considered pressed (or the press event was handled); otherwise false.</returns>
	bool IsPressed(bool pressed, int mx, int my) override;

	/// <summary>
	/// Moves an object or entity by the specified displacement along the vertical (y) axis.
	/// </summary>
	/// <param name="y">The displacement along the vertical (y) axis (in the coordinate units used).</param>
	void Move(float y);

	/// <summary>
	/// Renders content to the given SFML render window. Overrides the base class implementation.
	/// </summary>
	/// <param name="window">A non-const reference to the SFML sf::RenderWindow that drawing operations will be performed on.</param>
	void Render(sf::RenderWindow& window) override;

	/// <summary>
	/// Sets the object's vertical position to the given y coordinate, clamping it inside the track's vertical bounds and keeping the x coordinate at properties.x.
	/// </summary>
	/// <param name="y">Desired vertical position. This value is clamped to the range [track.y + 1, track.y + track.height - properties.height] before being applied.</param>
	void SetPosition(float y) {
		float yBound = std::min(std::max(y, track.y + 1), track.y + track.height - properties.height);
		Button::SetPosition(properties.x, yBound);
	}

	/// <summary>
	/// Overrides SetSize to apply a new size and adjust vertical position if the height change would move the control out of bounds.
	/// </summary>
	/// <param name="width">The new width to apply to the control.</param>
	/// <param name="height">The new height to apply. If the height change would place the control outside allowed bounds, the function adjusts the control's vertical position before applying the new size.</param>
	void SetSize(float width, float height) override {
		if (!InBounds(properties.y, height))
			SetPosition(properties.y - (height - properties.height));
		Button::SetSize(width, height);
	}

	/// <summary>
	/// Returns the current scroll position as a normalized fraction of the track's scrollable range.
	/// </summary>
	/// <returns>A float computed as (properties.y - track.y) / (track.height - properties.height). Typically 0.0 corresponds to the start/top and 1.0 to the end/bottom of the track. If track.height equals properties.height the result is undefined (division by zero).</returns>
	float GetScrollPercent() const {
		return (properties.y - track.y) / (track.height - properties.height);
	}

private:
	Properties track; // Properties defining the track (background) of the scroll bar
	int mousePos; // Variable to store the mouse position during dragging operations

	bool InBounds(float y, float height) const; // Private helper function that checks if a given vertical position (y) and height would keep the scroll bar within the vertical bounds of the track. Returns true if the position is valid, false otherwise.
};

