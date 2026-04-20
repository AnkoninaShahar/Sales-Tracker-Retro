#pragma once
#include "Button.h"

class ScrollBar : public Button
{
public:
	ScrollBar(Properties background = Properties(), Properties bar = Properties(), std::string text = "") :
		background(background), Button(bar, text) { }

	void Press() override {}

	void Render(sf::RenderWindow& window) override {
		sf::RectangleShape backgroundShape({ background.width, background.height });
		backgroundShape.setPosition({ background.x, background.y });
		backgroundShape.setFillColor(background.color);

		sf::RectangleShape barShape({ properties.width, properties.height });
		barShape.setPosition({ properties.x, properties.y });
		barShape.setFillColor(properties.color);

		window.draw(backgroundShape);
		window.draw(barShape);
	}

private:
	Properties background;
};

