#include "TextBox.h"


// TEXTBOX
// ___________________________________________________________________________

// Public

TextBox::TextBox(Properties properties, std::string empty, std::string text, std::string font) :
	empty(empty), Button(properties, text, font) 
{
	// Load keyboard sound effects into buffers and create sound objects
	for (int i = 0; i < 5; ++i) {
		keyboardBuffers[i] = sf::SoundBuffer("Assets\\Sounds\\keyboard_" + std::to_string(i + 1) + ".mp3");
		keyboardSounds[i] = new sf::Sound(keyboardBuffers[i]);
		keyboardSounds[i]->setVolume(40);
	}
}

TextBox::~TextBox() noexcept {
	// Clean up dynamically allocated sound objects
	for (int i = 0; i < 5; ++i) {
		delete keyboardSounds[i];
	}
}

void TextBox::Press() noexcept {
	editing = true; // Set the editing state to true when the text box is pressed
	clickSound->play(); // Play the click sound effect when the text box is pressed
}

bool TextBox::IsPressed(bool pressed, int mx, int my) {
	// Check if the mouse is within the bounds of the text box
	bool inBounds = (mx >= properties.x && mx <= properties.x + properties.width) && (my >= properties.y && my <= properties.y + properties.height);

	// If the text box is pressed but the mouse is not within bounds and the status is not already PRESSED, set editing to false
	if (pressed && !inBounds && status != PRESSED)
		editing = false;

	return Button::IsPressed(pressed, mx, my); // Call the base class IsPressed to handle the button press logic and return its result
}

void TextBox::Edit(char character) {
	// Handle character input for the text box when it is in editing mode
	if (editing) {
		// If the character is a backspace, remove the last character from the text if it is not empty. If the character is a carriage return, exit editing mode. If the character is a valid ASCII character (less than 128), append it to the text.
		if (character == '\b') {
			if (text.size() != 0)
				text.erase(text.size() - 1);
		}
		// If the character is a carriage return, exit editing mode.
		else if (character == '\r')
			editing = false;
		// If the character is a valid ASCII character (less than 128), append it to the text.
		else if (character < 128)
			text += character;

		// Play a random keyboard sound effect from the loaded buffers to provide feedback for the character input
		int choice = std::rand() % 5;
		keyboardSounds[choice]->play();
	}
}

void TextBox::Render(sf::RenderWindow& window) {
	// Create a rectangle shape for the text box background and set its position, fill color, and outline thickness
	sf::RectangleShape rect({ properties.width, properties.height });
	rect.setPosition({ properties.x, properties.y });
	rect.setFillColor(sf::Color(227, 227, 227));
	rect.setOutlineThickness(5);

	sf::Text text(font, this->text); // Create an SFML Text object using the loaded font and the current text of the text box

	// Set the outline color of the rectangle based on the editing state and hover status of the text box
	if (!editing && status == HOVER)
		rect.setOutlineColor(sf::Color(122, 122, 122));
	else if (editing)
		rect.setOutlineColor(sf::Color(184, 48, 48));
	else
		rect.setOutlineColor(sf::Color(46, 46, 46));

	window.draw(rect); // Draw the rectangle shape for the text box background onto the window

	// Set the string and fill color of the text based on whether the text box is empty or not. If the text box is empty, display the placeholder (empty) text in a lighter color; otherwise, display the actual text in a darker color.
	if (this->text != "") {
		text.setString(this->text);
		text.setFillColor(sf::Color(59, 59, 59));
	}
	else {
		text.setString(empty);
		text.setFillColor(sf::Color(138, 138, 138));
	}

	// Calculate the character size for the text to fit within the text box, with a maximum size of 30. The character size is determined by the width of the text box and the length of the text, ensuring that it scales appropriately as the text changes.
	int characterSize = std::min((properties.width * 2.2) / (this->text.length() + 1), 30.0);
	text.setCharacterSize(characterSize);
	text.setOrigin(
		{
		text.getLocalBounds().position.x - 5,
		text.getLocalBounds().position.y + text.getLocalBounds().size.y / 2
		}
	);
	text.setPosition({ properties.x , properties.y + properties.height / 2 });

	window.draw(text); // Draw the text onto the window, rendering the current content of the text box with the appropriate styling and positioning
}


// PRICE BOX
// ___________________________________________________________________________

void PriceBox::Edit(char character) {
	// Handle character input for the price box, allowing only digits, backspace, carriage return, and a single decimal point. 
	// Also enforce a maximum length of 3 characters before the decimal point and 2 characters after the decimal point.
	bool exception = character == '\b' || character == '\r';
	bool decimal = (text.size() > 0 && std::find(text.begin(), text.end(), '.') == text.end()) && character == '.';
	bool maxLenth = text.size() <= 3 || (text.size() > 3 && std::find(text.begin(), text.end(), '.') != text.end() - 3) || exception;
	if ((std::isdigit(character) || exception || decimal) && maxLenth)
		TextBox::Edit(character);

	// After editing the text, attempt to convert it to a float and format it as a price string. 
	if (text.size() > 0) { 	// If the text is not empty, parse it as a float and format it with two decimal places prefixed by a dollar sign. 
		price = std::stof(text);
		fText = std::format("${0:.2f}", price);
	}
	else {	// If the text is empty, reset the price to 0 and clear the formatted text.
		price = 0.0f;
		text = "";
		fText = "";
	}
}

void PriceBox::Render(sf::RenderWindow& window) {
	// Temporarily store the current text, set the text to the formatted price string (fText), 
	// call the base class Render to draw the price box, and then restore the original text. 
	// This allows the price box to display the formatted price while still maintaining the underlying text for editing purposes.
	std::string tempText = text;
	text = fText;
	TextBox::Render(window);
	text = tempText;
}