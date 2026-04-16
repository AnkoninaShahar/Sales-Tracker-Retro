#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Item.h"
#include "Button.h"
#include "Buttons.h"

class ScreenManager
{
public:
	ScreenManager() {
		std::vector<Item>* items = new std::vector<Item>();
		add = new Add(items, 100, 100, 200, 100);
	}

	void Render(sf::RenderWindow& window) {
		add->Render(window);
	}

private:
	std::vector<Item>* items = nullptr;
	Button* add = nullptr;
};

