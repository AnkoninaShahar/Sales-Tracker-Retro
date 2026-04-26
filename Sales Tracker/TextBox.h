#pragma once
#include "Button.h"

class TextBox : public Button
{
public:
	TextBox(Properties properties = Properties(), std::string empty = "", std::string text = "", std::string font = "Fonts\\Thraex.ttf");
	~TextBox() noexcept;

	void Press() override;
	bool IsPressed(bool pressed, int mx, int my) override;

	virtual void Edit(char character);
	void ResetEditing();

	virtual void Render(sf::RenderWindow& window) override;

private:
	bool editing = false;
	std::string empty;

	sf::SoundBuffer keyboardBuffers[5];
	sf::Sound* keyboardSounds[5];
};



class PriceBox : public TextBox
{
public:
	using TextBox::TextBox;

	void Edit(char character) override;

	void Render(sf::RenderWindow& window) override;

private:
	float price = 0.0f;
	std::string fText = "";
};

