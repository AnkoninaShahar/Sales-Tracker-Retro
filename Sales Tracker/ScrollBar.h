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
		float yBound = std::min(std::max(y, background.y + 1), background.y + background.height - properties.height);
		Button::SetPosition(x, yBound);
	}

	void SetSize(float width, float height) override {
		if (!InBounds(properties.y, height))
			SetPosition(properties.x, properties.y - (height - properties.height));
		Button::SetSize(width, height);
	}

	float GetScrollPercent() {
		return (properties.y - background.y) / (background.height - properties.height);
	}

private:
	Properties background;
	int my;

	bool InBounds(float y, float height);
};

