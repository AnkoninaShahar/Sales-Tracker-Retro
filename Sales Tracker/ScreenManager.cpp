#include "ScreenManager.h"

// Public

ScreenManager::ScreenManager() :
	items(std::vector<Item*>()),
	add(items, Properties(100, 100, 200, 100, sf::Color::Green)),
	bar(Properties(840, 240, 40, 300, sf::Color::Green),
		Properties(845, 245, 30, 50, sf::Color::Blue))
{
	scrollView.setSize({ 700, 330 });
	scrollView.setViewport(sf::FloatRect({ 0.2f, 0.4f }, { 0.5f, 0.5f }));
	scroll = 0;
	prevScroll = 0;
}

ScreenManager::~ScreenManager() {
	for (Item* item : items) {
		delete item;
	}
}

void ScreenManager::Scroll(float scroll, sf::RenderWindow& window) {
	int maxScroll = -70 * static_cast<int>((items.size() - 5)) - 30;
	if (this->scroll <= 0 || this->scroll >= maxScroll) {
		if (MouseInScrollWindow(sf::Mouse::getPosition(window), window) && items.size() > 4)
			this->scroll += scroll * 10;
		bar.Move(0, -scroll * 10);
	}
}

void ScreenManager::EditItem(char character) {
	for (Item* item : items) {
		item->Edit(character);
	}
}

void ScreenManager::EndEditing() {
	for (Item* item : items) {
		item->EndEdit();
	}
}

void ScreenManager::Render(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	RenderUI(mousePos, window);

	CorrectScroll();
}

void ScreenManager::RenderUI(sf::Vector2i mousePos, sf::RenderWindow& window) {
	// RENDER ADD BUTTON
	//_____________________________________________________
	window.setView(window.getDefaultView());
	add.Render(window);
	if (add.IsPressed(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), mousePos.x, mousePos.y))
		add.Press();

	// RENDER SCROLL BAR
	//_____________________________________________________
	float length = 300;
	for (int i = 0; i < static_cast<int>(items.size() - 4); ++i) {
		length -= length / (i + 4);
	}
	bar.SetSize(bar.GetSize().x, length);
	bar.Render(window);
	if (bar.IsPressed(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), mousePos.x, mousePos.y)) {
		bar.Press();
		scroll = bar.GetScroll();
	}

	// RENDER ITEM WINDOW
	//_____________________________________________________
	sf::FloatRect rect = sf::FloatRect(
		{ scrollView.getViewport().position.x * window.getSize().x, scrollView.getViewport().position.y * window.getSize().y },
		{ scrollView.getViewport().size.x * window.getSize().x, scrollView.getViewport().size.y * window.getSize().y }
	);
	sf::RectangleShape shape = sf::RectangleShape({ rect.size.x, rect.size.y });
	shape.setPosition({ rect.position.x, rect.position.y });
	window.draw(shape);

	// RENDER ITEMS
	//_____________________________________________________	
	window.setView(scrollView);
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, scrollView);

	if (items.size() > 0) {
		for (int i = 0; i < items.size(); ++i) {
			if (items[i]->Interact(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), static_cast<int>(worldPos.x), static_cast<int>(worldPos.y))) {
				--i;
				continue;
			}
			items[i]->SetPosition(150, 350 + i * 70 + scroll);
			items[i]->Render(window);
		}
	}
}

// Private

bool ScreenManager::MouseInScrollWindow(sf::Vector2i mousePos, sf::RenderWindow& window) {
	sf::FloatRect rect = scrollView.getViewport();
	return (mousePos.x >= rect.position.x * window.getSize().x && mousePos.x <= (rect.position.x + rect.size.x) * window.getSize().x)
		&& (mousePos.y >= rect.position.y * window.getSize().y && mousePos.y <= (rect.position.y + rect.size.y) * window.getSize().y);
}

void ScreenManager::CorrectScroll() {
	int maxScroll = -70 * static_cast<int>((items.size() - 5)) - 30;
	if (prevScroll == scroll) {
		if (scroll > 0)
			scroll -= scroll / 5;
		else if (scroll < maxScroll)
			scroll -= (scroll - maxScroll) / 5;
	}
	else
		prevScroll = scroll;

}