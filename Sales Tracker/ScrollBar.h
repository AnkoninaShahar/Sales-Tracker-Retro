#pragma once
#include "Button.h"

class ScrollBar : public Button
{
public:
	ScrollBar(Properties background = Properties(), Properties bar = Properties(), std::string text = "") :
		background(background), Button(bar, text) { }

	void Press() override {
		SetPosition(properties.x, my - properties.height / 2);
	}

	virtual bool IsPressed(bool pressed, int mx, int my) {
		bool result = pressed &&
			(mx >= properties.x && mx <= properties.x + properties.width) &&
			(my >= properties.y && my <= properties.y + properties.height);

		this->my = my;

		return result;
	}

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

	void Move(float x, float y) override {
		if (InBounds(properties.y + y, properties.height))
			Button::Move(x, y);
	}

	void SetPosition(float x, float y) override {
		if (InBounds(y, properties.height))
			Button::SetPosition(x, y);
	}

	void SetSize(float width, float height) override {
		if (InBounds(properties.y, height))
			Button::SetSize(width, height);
	}

private:
	Properties background;
	float my;

	bool InBounds(float y, float height) {
		return (y > background.y && y + height < background.y + background.height);
	}
};

