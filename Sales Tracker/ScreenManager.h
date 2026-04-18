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
	ScreenManager() : items(std::vector<Item*>()), add(items, Properties(100, 100, 200, 100, sf::Color::Green)) {
		scrollView.setSize({ 700, 330 });
		scrollView.setViewport(sf::FloatRect({ 0.25f, 0.4f }, { 0.5f, 0.5f }));
	}

	~ScreenManager() {
		for (Item* item : items) {
			delete item;
		}
	}

	void Render(sf::RenderWindow& window) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		RenderButtons(mousePos, window);
		RenderItems(mousePos, window);
	}

private:
	std::vector<Item*> items;
	Add add;

	sf::View scrollView;

	void RenderButtons(sf::Vector2i mousePos, sf::RenderWindow& window) {
		window.setView(window.getDefaultView());
		add.Render(window);
		if (add.IsPressed(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), mousePos.x, mousePos.y))
			add.Press();
	}
	
	void RenderItems(sf::Vector2i mousePos, sf::RenderWindow& window) {
		window.setView(scrollView);
		if (items.size() > 0) {
			for (int i = 0; i < items.size(); ++i) {
				if (items[i]->Interact(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), mousePos.x, mousePos.y)) {
					--i;
					continue;
				}
				items[i]->SetPosition(150, 350 + i * 70);
				items[i]->Render(window);
			}
		}
	}
};

