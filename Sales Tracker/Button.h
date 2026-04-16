#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Helper.h"

using namespace Helper;

class Button
{
public:
	Button(Properties properties, std::string text = "") : properties(properties), text(text) {}

	Button(Button& other) {
		properties = other.properties;
		text = other.text;
	}

	virtual ~Button() {}

	virtual void Press() = 0;

	bool IsPressed(float mx, float my) {
		return (mx >= properties.x && mx <= properties.x + properties.width) && (my >= properties.y && my <= properties.y + properties.height);
	}

	void Render(sf::RenderWindow& window) {
		sf::RectangleShape button({ properties.width, properties.height});
		button.setPosition({ properties.x, properties.y });
		button.setFillColor(properties.color);
		window.draw(button);
	}

	void SetPosition(float x, float y) {
		this->properties.x = x;
		this->properties.y = y;
	}

	void SetSize(float width, float height) {
		this->properties.width = width;
		this->properties.height = height;
	}
	
	void SetText(std::string text) {
		this->text = text;
	}

	void Print() {
		std::cout << ToString() << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& os, const Button& button) {
		return os << button.ToString() << std::endl;
	}

protected:
	Properties properties;
	std::string text;

	std::string ToString() const {
		return "POSITION: ( " + std::to_string(properties.x) + ", " + std::to_string(properties.y) + " )\tSIZE: " + std::to_string(properties.width) + "x" + std::to_string(properties.height) + "\n";
	}
};

