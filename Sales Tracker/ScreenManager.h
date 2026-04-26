#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Item.h"
#include "Button.h"
#include "Buttons.h"
#include "Helper.h"
#include "ScrollBar.h"

using namespace Helper;

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	void Scroll(float scroll, sf::RenderWindow& window);

	void EditItem(char character);

	void Render(sf::RenderWindow& window);

private:
	std::vector<Item*> items;
	Add add;
	ScrollBar bar;

	sf::View scrollView;
	float scroll, prevScroll;
	int scrollTime = 0;
	bool scrollEdge = false;

	sf::Font font;
	sf::Texture logo;

	void RenderBackground(sf::RenderWindow& window);
	void RenderUI(sf::Vector2i mousePos, sf::RenderWindow& window);

	bool MouseInScrollWindow(sf::Vector2i mousePos, sf::RenderWindow& window);
	void CorrectScroll();
};

