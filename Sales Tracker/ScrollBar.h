#pragma once
#include "Button.h"

class ScrollBar : public Button
{
public:
	ScrollBar(Properties background = Properties(), Properties bar = Properties(), std::string text = "");

	void Press() override;
	bool IsPressed(bool pressed, int mx, int my) override;

	void Move(float x, float y) override;

	void Render(sf::RenderWindow& window) override;

	void SetPosition(float x, float y) override {
		if (InBounds(y, properties.height))
			Button::SetPosition(x, y);
	}

	void SetSize(float width, float height) override {
		if (InBounds(properties.y, height))
			Button::SetSize(width, height);
	}

	float GetScroll() {
		return background.y - properties.y;
	}

	float GetTotalScroll() {
		return background.y - properties.height;
	}

private:
	Properties background;
	int my;

	bool InBounds(float y, float height);
};

