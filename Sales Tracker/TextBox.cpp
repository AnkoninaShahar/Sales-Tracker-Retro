#include "TextBox.h"


// TEXTBOX
// ___________________________________________________________________________

// Public

TextBox::TextBox(Properties properties, std::string empty, std::string text, std::string font) :
	empty(empty), Button(properties, text, font) 
{
	for (int i = 0; i < 5; ++i) {
		keyboardBuffers[i] = sf::SoundBuffer("Sounds\\keyboard_" + std::to_string(i + 1) + ".mp3");
		keyboardSounds[i] = new sf::Sound(keyboardBuffers[i]);
		keyboardSounds[i]->setVolume(20);
	}
}

TextBox::~TextBox() noexcept {
	for (int i = 0; i < 5; ++i) {
		delete keyboardSounds[i];
	}
}

void TextBox::Press() {
	editing = true;

	clickSound->play();
}

bool TextBox::IsPressed(bool pressed, int mx, int my) {
	bool inBounds = (mx >= properties.x && mx <= properties.x + properties.width) && (my >= properties.y && my <= properties.y + properties.height);

	if (pressed && !inBounds && status != PRESSED)
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

		int choice = std::rand() % 5;
		keyboardSounds[choice]->play();
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

	sf::Text text(font, this->text);

	if (!editing && status == HOVER)
		rect.setOutlineColor(sf::Color(122, 122, 122));
	else if (editing)
		rect.setOutlineColor(sf::Color(184, 48, 48));
	else
		rect.setOutlineColor(sf::Color(46, 46, 46));

	window.draw(rect);

	if (this->text != "") {
		text.setString(this->text);
		text.setFillColor(sf::Color(59, 59, 59));
	}
	else {
		text.setString(empty);
		text.setFillColor(sf::Color(138, 138, 138));
	}

	int characterSize = std::min((properties.width * 2.2) / (this->text.length() + 1), 30.0);
	text.setCharacterSize(characterSize);
	text.setOrigin(
		{
		text.getLocalBounds().position.x - 5,
		text.getLocalBounds().position.y + text.getLocalBounds().size.y / 2
		}
	);
	text.setPosition({ properties.x , properties.y + properties.height / 2 });

	window.draw(text);
}


// PRICE BOX
// ___________________________________________________________________________

void PriceBox::Edit(char character) {
	bool exception = character == '\b' || character == '\r';
	if (std::isdigit(character) || exception
		|| ((text.size() > 0 && std::find(text.begin(), text.end(), '.') == text.end()) && character == '.')) {

		if (text.size() <= 3 || (text.size() > 3 && std::find(text.begin(), text.end(), '.') != text.end() - 3) || exception)
			TextBox::Edit(character);
	}

	if (text.size() > 0) {
		price = std::stof(text);
		fText = std::format("${0:.2f}", price);
	}
	else {
		price = 0.0f;
		text = "";
		fText = "";
	}
}

void PriceBox::Render(sf::RenderWindow& window) {
	std::string tempText = text;
	text = fText;
	TextBox::Render(window);
	text = tempText;
}