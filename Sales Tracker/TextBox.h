#pragma once
#include "Button.h"

class TextBox : public Button
{
public:
	TextBox(Properties properties = Properties(), std::string empty = "", std::string text = "", std::string font = "Fonts\\Thraex.ttf");
	~TextBox() {}

	void Press() override;
	bool IsPressed(bool pressed, int mx, int my) override;

	void Edit(char character);
	void ResetEditing();

	void Render(sf::RenderWindow& window) override;

private:
	bool editing = false;
	std::string empty;
};

