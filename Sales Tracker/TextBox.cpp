#include "TextBox.h"

// Public

TextBox::TextBox(Properties properties, std::string empty, std::string text, std::string font) :
	empty(empty), Button(properties, text, font) {}

void TextBox::Press() {
	editing = true;
}

bool TextBox::IsPressed(bool pressed, int mx, int my) {
	bool inBounds = 
		(mx >= properties.x && mx <= properties.x + properties.width) &&
		(my >= properties.y && my <= properties.y + properties.height);

	if (pressed && !inBounds && !held)
		editing = false;

	return Button::IsPressed(pressed, mx, my);
}

void TextBox::Edit(char character) {
	if (editing) {
		if (character == '\b') {
			if (text.size() != 0)
				text.erase(text.size() - 1);
		}
		else if (character == '\r')
			editing = false;
		else if (character < 128)
			text += character;
	}
}

void TextBox::ResetEditing() {
	editing = false;
}

void TextBox::Render(sf::RenderWindow& window) {
	sf::RectangleShape rect({ properties.width, properties.height });
	rect.setPosition({ properties.x, properties.y });

	sf::Text string(font, text);

	int characterSize = std::min((properties.width * 2.2) / (text.length() + 1), 30.0);
	string.setCharacterSize(characterSize);
	string.setPosition({ properties.x, properties.y + properties.height / 4 });

	if (editing)
		rect.setFillColor(sf::Color::Green);
	else
		rect.setFillColor(sf::Color::Yellow);

	if (text != "") {
		string.setString(text);
		string.setFillColor(sf::Color::Black);
	}
	else {
		string.setString(empty);
		string.setFillColor(sf::Color::Magenta);
	}

	window.draw(rect);
	window.draw(string);
}