#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Button
{
public:
	Button(float x = 0, float y = 0, float width = 0, float height = 0, sf::Color color = sf::Color::White, std::string text = "") :
		x(x), y(y), width(width), height(height), color(color), text(text) {}

	Button(Button& other) {
		x = other.x;
		y = other.y;
		width = other.width;
		height = other.height;
		color = other.color;
		text = other.text;
	}

	virtual ~Button() {}

	virtual void Press() = 0;

	bool IsPressed(float mx, float my) {
		return (mx >= x && mx <= x + width) && (my >= y && my <= y + height);
	}

	void Render(sf::RenderWindow& window) {
		sf::RectangleShape button({width, height});
		button.setPosition({ x, y });
		button.setFillColor(color);
		window.draw(button);
	}

	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void SetSize(float width, float height) {
		this->width = width;
		this->height = height;
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
	float x, y;
	float width, height;
	std::string text;
	sf::Color color;

	std::string ToString() const {
		return "POSITION: ( " + std::to_string(x) + ", " + std::to_string(y) + " )\tSIZE: " + std::to_string(width) + "x" + std::to_string(height) + "\n";
	}
};

