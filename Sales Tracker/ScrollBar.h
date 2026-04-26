#pragma once
#include "Button.h"

class ScrollBar : public Button
{
public:
	ScrollBar(Properties track = Properties(), Properties bar = Properties(), std::string text = "");

	void Press() override;
	bool IsPressed(bool pressed, int mx, int my) override;

	void Move(float y);

	void Render(sf::RenderWindow& window) override;

	void SetPosition(float y) {
		float yBound = std::min(std::max(y, track.y + 1), track.y + track.height - properties.height);
		Button::SetPosition(properties.x, yBound);
	}

	void SetSize(float width, float height) override {
		if (!InBounds(properties.y, height))
			SetPosition(properties.y - (height - properties.height));
		Button::SetSize(width, height);
	}

	float GetScrollPercent() const {
		return (properties.y - track.y) / (track.height - properties.height);
	}

private:
	Properties track;
	int mousePos;

	bool InBounds(float y, float height) const;
};

