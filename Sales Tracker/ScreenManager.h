#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Item.h"
#include "Button.h"
#include "Buttons.h"
#include "Helper.h"

using namespace Helper;

class ScreenManager
{
public:
	ScreenManager() {
		items = std::vector<Item*>();
		add = new Add(items, Properties(100, 100, 200, 100, sf::Color::Green));
	}

	void Render(sf::RenderWindow& window) {
		Act(window);

		add->Render(window);
		if (items.size() > 0) {
			for (int i = 0; i < items.size(); ++i) {
				items[i]->SetPosition(100, 220 + i * 70);
				items[i]->Render(window);
			}
		}
	}

private:
	std::vector<Item*> items;
	Button* add = nullptr;

	void Act(sf::RenderWindow& window) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (add->IsPressed(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), mousePos.x, mousePos.y))
			add->Press();

		if (items.size() > 0) {
			for (Item* item : items) {
				item->Interact(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), mousePos.x, mousePos.y);
			}
		}
	}
};

