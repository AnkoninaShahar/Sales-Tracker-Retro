#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Helper.h"

using namespace Helper;

class Button
{
public:
	Button(Properties properties = Properties(), std::string text = "", std::string font = "Fonts\\Thraex.ttf");
	Button(Button& other);
	virtual ~Button();

	virtual void Press() = 0;
	virtual bool IsPressed(bool pressed, int mx, int my);

	virtual void Move(float x, float y);

	virtual void Render(sf::RenderWindow& window);

	virtual void SetPosition(float x, float y) {
		properties.x = x;
		properties.y = y;
	}

	virtual void SetSize(float width, float height) {
		properties.width = width;
		properties.height = height;
	}
	
	virtual void SetText(std::string text) {
		this->text = text;
	}

	virtual sf::Vector2f GetPosition() {
		return sf::Vector2f(properties.x, properties.y);
	}

	virtual sf::Vector2f GetSize() {
		return sf::Vector2f(properties.width, properties.height);
	}

	virtual std::string GetText() {
		return text;
	}

	virtual void Print();

	friend std::ostream& operator<<(std::ostream& os, const Button& button) {
		return os << button.ToString() << std::endl;
	}

protected:
	Properties properties;

	std::string text;
	sf::Font font;

	virtual std::string ToString() const;

private:
	bool held = false;
};

