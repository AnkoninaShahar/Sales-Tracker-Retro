#include "ScrollBar.h"

// Public

ScrollBar::ScrollBar(Properties background, Properties bar, std::string text) :
	background(background), my(0), Button(bar, text) {}

void ScrollBar::Press() {
	SetPosition(properties.x, my - properties.height / 2);
}

bool ScrollBar::IsPressed(bool pressed, int mx, int my) {
	bool result = pressed &&
		(mx >= background.x && mx <= background.x + background.width) &&
		(my >= background.y && my <= background.y + background.height);

	if (result)
		held = true;
	if (!pressed)	
		held = false;

	this->my = my;

	return result || held;
}

void ScrollBar::Move(float x, float y) {
	if (InBounds(properties.y + y, properties.height))
		Button::Move(x, y);
}

void ScrollBar::Render(sf::RenderWindow& window) {
	sf::RectangleShape backgroundShape({ background.width, background.height });
	backgroundShape.setPosition({ background.x, background.y });
	backgroundShape.setFillColor(background.color);

	sf::RectangleShape barShape({ properties.width, properties.height });
	barShape.setPosition({ properties.x, properties.y });
	barShape.setFillColor(properties.color);

	window.draw(backgroundShape);
	window.draw(barShape);
}

// Private

bool ScrollBar::InBounds(float y, float height) {
	return (y > background.y && y + height < background.y + background.height);
}