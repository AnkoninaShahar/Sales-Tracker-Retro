#pragma once
#include "Button.h"

class TextBox : public Button
{
public:
	TextBox(Properties properties = Properties(), std::string text = "", std::string empty = "") : 
		empty(empty), Button(properties, text) {}

	~TextBox() {}

	void Press() override {
		editing = true;
	}

	void Edit(char character) {
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

	void Render(sf::RenderWindow& window) override {
		sf::Font font;
		if (font.openFromFile("Fonts\\Thraex.ttf")) {
			sf::Text string(font, text);
			if (text != "") 
				string.setFillColor(sf::Color::Black);
			else {
				string.setString("(Click here to edit)");
				string.setFillColor(sf::Color::Magenta);
			}
			string.setCharacterSize(30);
			string.setPosition({ properties.x, properties.y });
			window.draw(string);
		}
	}

	void ResetEditing() {
		editing = false;
	}

private:
	bool editing = false;
	std::string empty;
};

