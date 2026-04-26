#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <typeinfo>

#include "Helper.h"

using namespace Helper;

class Button
{
public:
	Button(Properties properties = Properties(), std::string text = "", std::string fontPath = "Fonts\\Thraex.ttf");
	Button(const Button& other) noexcept;
	virtual ~Button() noexcept;

	virtual void Press() = 0;
	virtual bool IsPressed(bool pressed, int mx, int my);
	virtual bool IsHovering(int mx, int my) const;

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

	virtual sf::Vector2f GetPosition() const {
		return sf::Vector2f(properties.x, properties.y);
	}

	virtual sf::Vector2f GetSize() const {
		return sf::Vector2f(properties.width, properties.height);
	}

	virtual std::string GetText() const {
		return text;
	}

	virtual void Print() const;

	friend std::ostream& operator<<(std::ostream& os, const Button& button) {
		return os << button.ToString() << std::endl;
	}

protected:
	Properties properties;
	std::string text;

	sf::Font font;
	sf::SoundBuffer clickBuffer;
	sf::Sound* clickSound;

	enum ButtonState {
		NONE,
		HOVER,
		PRESSED
	};
	ButtonState status;

	bool mousePressed;

	virtual std::string ToString() const;
};

