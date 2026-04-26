#include "TextBox.h"

// Public

TextBox::TextBox(Properties properties, std::string empty, std::string format, std::string text, std::string font) :
	empty(empty), format(format), Button(properties, text, font) {}

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
	rect.setFillColor(sf::Color(227, 227, 227));
	rect.setOutlineThickness(5);

	sf::Text string(font, std::format("{}", text));

	if (editing)
		rect.setOutlineColor(sf::Color(184, 48, 48));
	else
		rect.setOutlineColor(sf::Color(46, 46, 46));

	if (text != "") {
		string.setString(text);
		string.setFillColor(sf::Color(59, 59, 59));
	}
	else {
		string.setString(empty);
		string.setFillColor(sf::Color(138, 138, 138));
	}

	int characterSize = std::min((properties.width * 2.2) / (text.length() + 1), 30.0);
	string.setCharacterSize(characterSize);
	string.setOrigin(
		{
		string.getLocalBounds().position.x,
		string.getLocalBounds().position.y + string.getLocalBounds().size.y / 2
		}
	);
	string.setPosition({ properties.x , properties.y + properties.height / 2 });

	window.draw(rect);
	window.draw(string);
}