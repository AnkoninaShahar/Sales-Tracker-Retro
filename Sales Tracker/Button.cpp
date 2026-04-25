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
	int olRed = properties.color.r * 0.35;
	int olGreen = properties.color.g * 0.35;
	int olBlue = properties.color.b * 0.35;

	sf::RectangleShape button({ properties.width, properties.height });
	button.setPosition({ properties.x, properties.y });
	button.setFillColor(properties.color);
	button.setOutlineColor(sf::Color(olRed, olGreen, olBlue));
	button.setOutlineThickness(std::min(properties.width, properties.height) / 5);
	window.draw(button);

	sf::Text string(font, text);
	string.setCharacterSize(30);
	string.setOrigin(
		{ 
		string.getLocalBounds().position.x + string.getLocalBounds().size.x / 2, 
		string.getLocalBounds().position.y + string.getLocalBounds().size.y / 2 
		}
	);
	string.setPosition({ properties.x + properties.width / 2, properties.y + properties.height / 2 });
	string.setFillColor(sf::Color(59, 59, 59));
	window.draw(string);
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