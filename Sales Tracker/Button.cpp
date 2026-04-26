#include "Button.h"

// Public

Button::Button(Properties properties, std::string text, std::string fontPath) :
	properties(properties), text(text), status(NONE), mousePressed(false)
{
	try {
		if (!font.openFromFile(fontPath))
			throw "FAILED TO LOAD FONT:\t" + fontPath;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	try {
		if (!clickBuffer.loadFromFile("Sounds\\retro_click.mp3"))
			throw "FAILED TO LOAD FONT:\tretro_click.mp3";
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
	clickSound = new sf::Sound(clickBuffer);
	clickSound->setVolume(10);
}

Button::Button(const Button& other) noexcept {
	properties = other.properties;
	text = other.text;

	font = other.font;
	clickBuffer = other.clickBuffer;
	clickSound = other.clickSound;

	status = other.status;
	mousePressed = other.mousePressed;
}

Button::~Button() noexcept {
	delete clickSound;
}

bool Button::IsPressed(bool pressed, int mx, int my) {
	if (!mousePressed) {
		if (IsHovering(mx, my)) {
			if (pressed)
				status = PRESSED;
			else
				status = HOVER;
		}
		else if (!pressed)
			status = NONE;
	}

	bool result = status == PRESSED && !mousePressed;
	mousePressed = pressed;
	return result;
}

bool Button::IsHovering(int mx, int my) const {
	return (mx >= properties.x && mx <= properties.x + properties.width) && (my >= properties.y && my <= properties.y + properties.height);
}

void Button::Render(sf::RenderWindow& window) {
	int ol[3] = { properties.color.r * 0.35, properties.color.g * 0.35, properties.color.b * 0.35 };
	int h[3] = { properties.color.r * 1.3, properties.color.g * 1.3, properties.color.b * 1.3 };
	int p[3] = { properties.color.r * 0.7, properties.color.g * 0.7, properties.color.b * 0.7 };

	sf::RectangleShape button({ properties.width, properties.height });
	button.setPosition({ properties.x, properties.y });
	button.setOutlineColor(sf::Color(ol[0], ol[1], ol[2]));
	button.setOutlineThickness(std::min(properties.width, properties.height) / 5);

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

	window.draw(button);

	sf::Text text(font, this->text);
	text.setCharacterSize(30);
	text.setOrigin(
		{ 
		text.getLocalBounds().position.x + text.getLocalBounds().size.x / 2,
		text.getLocalBounds().position.y + text.getLocalBounds().size.y / 2
		}
	);
	text.setPosition({ properties.x + properties.width / 2, properties.y + properties.height / 2 });
	text.setFillColor(sf::Color(59, 59, 59));
	window.draw(text);
}

void Button::Move(float x, float y) {
	properties.x += x;
	properties.y += y;
}

void Button::Print() const {
	std::cout << ToString() << std::endl;
}

// Private

std::string Button::ToString() const {
	std::string textStatus;
	switch (status) {
	case 1: textStatus = "HOVER";
		break;
	case 2: textStatus = "PRESSED";
		break;
	default: textStatus = "NONE"; 
		break;
	}

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