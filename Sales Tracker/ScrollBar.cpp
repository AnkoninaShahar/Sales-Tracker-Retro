#include "ScrollBar.h"

// Public

ScrollBar::ScrollBar(Properties track, Properties bar, std::string text) :
	track(track), mousePos(0), Button(bar, text) {}

void ScrollBar::Press() {
	SetPosition(mousePos - properties.height / 2);
}

bool ScrollBar::IsPressed(bool pressed, int mx, int my) {
	bool result = pressed &&
		(mx >= track.x && mx <= track.x + track.width) &&
		(my >= track.y && my <= track.y + track.height);

	if (result)
		status = PRESSED;
	if (!mousePressed && !result)
		status = IsHovering(mx, my) ? HOVER : NONE;

	mousePos = my;

	mousePressed = pressed;

	return result || status == PRESSED;
}

void ScrollBar::Move(float y) {
	if (InBounds(properties.y + y, properties.height))
		Button::Move(properties.x, y);
}

void ScrollBar::Render(sf::RenderWindow& window) {
	sf::RectangleShape trackShape({ track.width, track.height });
	trackShape.setPosition({ track.x, track.y });
	trackShape.setFillColor(track.color);

	sf::RectangleShape barShape({ properties.width, properties.height });
	barShape.setPosition({ properties.x, properties.y });

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

	window.draw(trackShape);
	window.draw(barShape);
}

// Private

bool ScrollBar::InBounds(float y, float height) const {
	return (y > track.y && y + height < track.y + track.height);
}