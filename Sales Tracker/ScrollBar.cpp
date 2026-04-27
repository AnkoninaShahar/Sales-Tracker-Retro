#include "ScrollBar.h"

// Public

ScrollBar::ScrollBar(Properties track, Properties bar, std::string text) :
	track(track), mousePos(0), Button(bar, text) {}

void ScrollBar::Press() noexcept {
	// Set the vertical position of the scroll bar to the current mouse position minus half of the scroll bar's height, effectively centering the scroll bar on the mouse cursor when pressed.
	SetPosition(mousePos - properties.height / 2); 
}

bool ScrollBar::IsPressed(bool pressed, int mx, int my) {
	// Determine if the scroll bar is considered pressed based on the current pressed state and mouse position. 
	bool result = pressed &&
		(mx >= track.x && mx <= track.x + track.width) &&
		(my >= track.y && my <= track.y + track.height);

	if (result) // If the scroll bar is currently being pressed, set the status to PRESSED. 
		status = PRESSED;
	if (!mousePressed && !result) // If the input is not pressed and the mouse is not within the track bounds, update the status to HOVER if the mouse is hovering over the scroll bar, or NONE otherwise.
		status = IsHovering(mx, my) ? HOVER : NONE;

	// Update the internal state of mousePressed to reflect the current pressed state and store the 
	// current mouse y-coordinate in mousePos for potential use in dragging the scroll bar.
	mousePos = my;
	mousePressed = pressed;

	return result || status == PRESSED; // Return true if the scroll bar is considered pressed or if its status is currently PRESSED; otherwise, return false.
}

void ScrollBar::Move(float y) {
	// Move the scroll bar vertically by the specified offset y, 
	// but only if the new position would still be within the vertical bounds of the track. 
	if (InBounds(properties.y + y, properties.height))
		Button::Move(properties.x, y);
}

void ScrollBar::Render(sf::RenderWindow& window) {
	// Create a rectangle shape for the track using the track properties and set its position and fill color based on the track's dimensions and color.
	sf::RectangleShape trackShape({ track.width, track.height });
	trackShape.setPosition({ track.x, track.y });
	trackShape.setFillColor(track.color);

	window.draw(trackShape); // Draw the track shape onto the window.

	// Create a rectangle shape for the scroll bar using the scroll bar properties and set its position. 
	sf::RectangleShape barShape({ properties.width, properties.height });
	barShape.setPosition({ properties.x, properties.y });

	// Set the fill color of the scroll bar based on its current status (HOVER, PRESSED, or default).
	switch (status) {
	case HOVER:
		barShape.setFillColor(sf::Color(200, 200, 200));
		break;
	case PRESSED:
		barShape.setFillColor(sf::Color(112, 112, 112));
		break;
	default:
		barShape.setFillColor(properties.color);
		break;
	}

	window.draw(barShape); // Draw the scroll bar shape onto the window.
}

// Private

bool ScrollBar::InBounds(float y, float height) const {
	// Check if the given vertical position y and height of the scroll bar would keep it within the vertical bounds of the track. 
	return (y > track.y && y + height < track.y + track.height); 
}