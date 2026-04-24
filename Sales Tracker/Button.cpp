#include "Button.h"

// Public

Button::Button(Properties properties, std::string text, std::string font) : 
	properties(properties), text(text) 
{
	try {
		if (!this->font.openFromFile(font))
			throw "FAILED TO LOAD FONT:\t" + font;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

Button::Button(Button& other) {
	properties = other.properties;
	text = other.text;
}

Button::~Button() {}

bool Button::IsPressed(bool pressed, int mx, int my) {
	bool result = pressed && !held &&
		(mx >= properties.x && mx <= properties.x + properties.width) &&
		(my >= properties.y && my <= properties.y + properties.height);

	if (pressed)
		held = true;
	else
		held = false;

	return result;
}

void Button::Render(sf::RenderWindow& window) {
	sf::RectangleShape button({ properties.width, properties.height });
	button.setPosition({ properties.x, properties.y });
	button.setFillColor(properties.color);
	window.draw(button);
}

void Button::Move(float x, float y) {
	properties.x += x;
	properties.y += y;
}

void Button::Print() {
	std::cout << ToString() << std::endl;
}

// Private

std::string Button::ToString() const {
	return "POSITION: ( " + std::to_string(properties.x) + ", " + std::to_string(properties.y) + " )\tSIZE: " + std::to_string(properties.width) + "x" + std::to_string(properties.height) + "\n";
}