#include "TextBox.h"

// Public

TextBox::TextBox(Properties properties, std::string empty, std::string text, std::string font) :
	empty(empty), Button(properties, text, font) {}

void TextBox::Press() {
	editing = true;
}

bool TextBox::IsPressed(bool pressed, int mx, int my) {
	bool result = Button::IsPressed(pressed, mx, my);

	if (pressed && !result)
		editing = false;

	return result;
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
	string.setCharacterSize(30);
	string.setPosition({ properties.x, properties.y });

	if (editing) {
		string.setString(text);
		string.setFillColor(sf::Color::Black);
		rect.setFillColor(sf::Color::Green);
	}
	else {
		if (text != "") {
			string.setFillColor(sf::Color::Black);
			rect.setFillColor(sf::Color::Yellow);
		}
		else {
			string.setString(empty);
			string.setFillColor(sf::Color::Magenta);
			rect.setFillColor(sf::Color::Yellow);
		}
	}

	window.draw(rect);
	window.draw(string);
}