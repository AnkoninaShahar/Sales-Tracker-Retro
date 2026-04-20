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
		scrollView.setViewport(sf::FloatRect({ 0.2f, 0.4f }, { 0.5f, 0.5f }));
		scroll = 0;
		deltaScroll = 0;
	}

	~ScreenManager() {
		for (Item* item : items) {
			delete item;
		}
	}

	void Render(sf::RenderWindow& window) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		RenderButtons(mousePos, window);

		sf::FloatRect rect = sf::FloatRect(
			{ scrollView.getViewport().position.x * window.getSize().x, scrollView.getViewport().position.y * window.getSize().y },
			{ scrollView.getViewport().size.x * window.getSize().x, scrollView.getViewport().size.y * window.getSize().y }
		);
		sf::RectangleShape shape = sf::RectangleShape({ rect.size.x, rect.size.y });
		shape.setPosition({ rect.position.x, rect.position.y });
		window.draw(shape);


		RenderItems(mousePos, window);

		CorrectScroll();
	}

	void Scroll(float scroll, sf::RenderWindow& window) {
		if (MouseInScrollWindow(sf::Mouse::getPosition(window), window) && items.size() > 4) {
			this->scroll += scroll * 10;
			deltaScroll = scroll;
		}
	}

	void ResetDeltaScroll() {
		deltaScroll = 0;
	}

	void EditItem(char character) {
		for (Item* item : items) {
			item->Edit(character);
		}
	}

	void EndEditing() {
		for (Item* item : items) {
			item->EndEdit();
		}
	}

private:
	std::vector<Item*> items;
	Add add;

	sf::View scrollView;
	float scroll, deltaScroll;

	void RenderButtons(sf::Vector2i mousePos, sf::RenderWindow& window) {
		window.setView(window.getDefaultView());
		add.Render(window);
		if (add.IsPressed(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), mousePos.x, mousePos.y))
			add.Press();
	}
	
	void RenderItems(sf::Vector2i mousePos, sf::RenderWindow& window) {
		window.setView(scrollView);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, scrollView);

		if (items.size() > 0) {
			for (int i = 0; i < items.size(); ++i) {
				if (items[i]->Interact(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), worldPos.x, worldPos.y)) {
					--i;
					continue;
				}
				items[i]->SetPosition(150, 350 + i * 70 + scroll);
				items[i]->Render(window);
			}
		}
	}

	bool MouseInScrollWindow(sf::Vector2i mousePos, sf::RenderWindow& window) {
		sf::FloatRect rect = scrollView.getViewport();
		return (mousePos.x >= rect.position.x * window.getSize().x && mousePos.x <= (rect.position.x + rect.size.x) * window.getSize().x)
			&& (mousePos.y >= rect.position.y * window.getSize().y && mousePos.y <= (rect.position.y + rect.size.y) * window.getSize().y);
	}

	void CorrectScroll() {
		int maxScroll = -70 * static_cast<int>((items.size() - 5)) - 30;
		if (deltaScroll < 0.1) {
			if (scroll > 0)
				scroll -= scroll / 10;
			else if (scroll < maxScroll)
				scroll -= (scroll - maxScroll) / 10;
		}
	}
};

