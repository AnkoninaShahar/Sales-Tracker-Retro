#include "Button.h"

// Public

Button::Button(Properties properties, std::string text, std::string fontPath) :
	properties(properties), text(text), status(NONE), mousePressed(false)
{
	// Load the font from the specified file path and handle any potential errors that may occur during loading. 
	// If the font fails to load, an error message is printed to the standard error stream.
	try {
		if (!font.openFromFile(fontPath))
			throw "FAILED TO LOAD FONT:\t" + fontPath;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	// Load the click sound effect from the specified file path and handle any potential errors that may occur during loading. 
	// If the sound file fails to load, an error message is printed to the standard error stream. If the sound is successfully loaded, 
	// a new sf::Sound object is created using the loaded sound buffer, and its volume is set to 10 for playback.
	try {
		if (!clickBuffer.loadFromFile("Assets\\Sounds\\retro_click.mp3"))
			throw "FAILED TO LOAD FONT:\tretro_click.mp3";
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
	clickSound = new sf::Sound(clickBuffer);
	clickSound->setVolume(30);
}

Button::Button(const Button& other) noexcept {
	// Perform a deep copy of the other Button's resources and member variables to ensure that the new instance operates 
	// independently without sharing resources that could lead to issues such as double deletion or unintended side effects. 
	properties = other.properties;
	text = other.text;

	font = other.font;
	clickBuffer = other.clickBuffer;
	clickSound = other.clickSound;

	status = other.status;
	mousePressed = other.mousePressed;
}

Button::~Button() noexcept {
	// Clean up dynamically allocated resources for the click sound to prevent memory leaks. 
	if (clickSound != nullptr)
		delete clickSound;
}

bool Button::IsPressed(bool pressed, int mx, int my) {
	// Check if the mouse was not previously pressed to determine if we should update the button's status based on 
	// the current mouse position and pressed state. 
	if (!mousePressed) { 
		if (IsHovering(mx, my)) { // If the mouse is hovering over the button, update the status to PRESSED if the input is currently pressed, or HOVER if it is not pressed.
			if (pressed)
				status = PRESSED;
			else // If the mouse is hovering but not pressed, update the status to HOVER.
				status = HOVER;
		}
		else if (!pressed) // If the mouse is not hovering over the button and the input is not pressed, update the status to NONE.
			status = NONE;
	}

	// The button is considered pressed if it is currently in the PRESSED state and the mouse was not previously pressed (indicating a new press event).
	// Update the mousePressed state to reflect the current pressed state for future interactions.
	bool result = status == PRESSED && !mousePressed; 
	mousePressed = pressed; 
	return result; // Return whether the button is considered pressed based on the current status and mouse pressed state.
}

bool Button::IsHovering(int mx, int my) const {
	// Check if the mouse coordinates (mx, my) are within the bounds of the button defined by its properties.
	return (mx >= properties.x && mx <= properties.x + properties.width) && (my >= properties.y && my <= properties.y + properties.height);
}

void Button::Render(sf::RenderWindow& window) {
	// Calculate the outline color, hover color, and pressed color based on the button's properties color. 
	int ol[3] = { properties.color.r * 0.35, properties.color.g * 0.35, properties.color.b * 0.35 };
	int h[3] = { properties.color.r * 1.3, properties.color.g * 1.3, properties.color.b * 1.3 };
	int p[3] = { properties.color.r * 0.7, properties.color.g * 0.7, properties.color.b * 0.7 };

	// Create a rectangle shape representing the button using SFML's sf::RectangleShape class. 
	sf::RectangleShape button({ properties.width, properties.height });
	button.setPosition({ properties.x, properties.y });
	button.setOutlineColor(sf::Color(ol[0], ol[1], ol[2]));
	button.setOutlineThickness(std::min(properties.width, properties.height) / 5);

	// Set the fill color of the button based on its current status. 
	switch (status) {
	case HOVER:
		button.setFillColor(sf::Color(h[0], h[1], h[2]));
		break;
	case PRESSED:
		button.setFillColor(sf::Color(p[0], p[1], p[2]));
		break;
	default:
		button.setFillColor(properties.color);
		break;
	}

	window.draw(button); // Draw the button rectangle onto the provided SFML render window to visually represent the button in the user interface.

	// Create a text object using SFML's sf::Text class to display the button's text. 
	sf::Text text(font, this->text);
	text.setCharacterSize(30);
	text.setOrigin(
		{ 
		text.getLocalBounds().position.x + text.getLocalBounds().size.x / 2,
		text.getLocalBounds().position.y + text.getLocalBounds().size.y / 2
		}
	);
	text.setPosition({ properties.x + properties.width / 2, properties.y + properties.height / 2 });
	text.setFillColor(sf::Color(20, 20, 20));
	window.draw(text); // Draw the text onto the window to visually represent the button's label in the user interface.
}

void Button::Move(float x, float y) {
	// Update the button's position by adding the specified x and y offsets to its current position.
	properties.x += x;
	properties.y += y;
}

void Button::Print() const {
	std::cout << ToString() << std::endl; // Print the string representation of the button to the standard output stream. 
}

// Private

std::string Button::ToString() const {
	// Convert the button's current status to a human-readable string representation for debugging purposes. 
	std::string textStatus;
	switch (status) {
	case 1: textStatus = "HOVER";
		break;
	case 2: textStatus = "PRESSED";
		break;
	default: textStatus = "NONE"; 
		break;
	}

	// Generate a string representation of the button, including its class name, position, size, color, text, and current state.
	std::string className = typeid(*this).name();
	std::string title = "===================================================================================================\n\n" + 
						className + 
						"\n---------------";
	std::string position = std::format("POSITION [x, y]: ( {0:.2f}, {1:.2f} )\t", properties.x, properties.y);
	std::string size = std::format("SIZE [width x height]: {0:.2f} x {1:.2f}\t", properties.width, properties.height);
	std::string color = std::format("COLOR [r, g, b]: ( {0}, {1}, {2} )\t", properties.color.r, properties.color.g, properties.color.b);
	std::string text = "TEXT: \"" + this->text + "\"\t";
	std::string state = "STATE: " + textStatus + "\t";
	std::string end = "===================================================================================================";
	return title + "\n\n" + position + size + "\n\n" + color + text + state + "\n\n" + end + "\n";
}