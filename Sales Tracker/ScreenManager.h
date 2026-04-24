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
	void ResetDeltaScroll();

	void EditItem(char character);
	void EndEditing();

	void Render(sf::RenderWindow& window);

private:
	std::vector<Item*> items;
	Add add;
	ScrollBar bar;

	sf::View scrollView;
	float scroll, prevScroll;
	bool scrollEdge = false;

	void RenderUI(sf::Vector2i mousePos, sf::RenderWindow& window);

	bool MouseInScrollWindow(sf::Vector2i mousePos, sf::RenderWindow& window);
	void CorrectScroll();
};

