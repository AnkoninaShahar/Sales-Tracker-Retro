#include "ScreenManager.h"

// Public

ScreenManager::ScreenManager() :
	items(std::vector<Item*>()),
	add(items, Properties(230, 90, 200, 50, sf::Color(54, 176, 46)), "ADD ITEM", "Fonts\\Shelten.ttf"),
	bar(Properties(828, 180, 40, 300, sf::Color(18, 18, 18)),
		Properties(833, 185, 30, 50, sf::Color(166, 166, 166)))
{
	scrollView.setSize({ 700, 330 });
	scrollView.setViewport(sf::FloatRect({ 0.2f, 0.3f }, { 0.54f, 0.5f }));
	scroll = 0;
	prevScroll = 0;

	std::string font = "Fonts\\Shelten.ttf";
	std::string logoPath = "Sprites\\gift_logo.png";

	try {
		if (!this->font.openFromFile(font))
			throw "FAILED TO LOAD FONT:\t" + font;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	try {
		if (!logo.loadFromFile(logoPath))
			throw "FAILED TO LOAD TEXTURE:\t" + logoPath;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

ScreenManager::~ScreenManager() {
	for (Item* item : items) {
		delete item;
	}
}

void ScreenManager::Scroll(float scroll, sf::RenderWindow& window) {
	if (MouseInScrollWindow(sf::Mouse::getPosition(window), window) && items.size() > 4)
		this->scroll += scroll * 10;
}

void ScreenManager::EditItem(char character) {
	for (Item* item : items) {
		item->Edit(character);
	}
}

void ScreenManager::Render(sf::RenderWindow& window) {
	if (items.size() < 5) {
		scroll = 0;
		bar.SetPosition(bar.GetPosition().x, 185);
	}

	RenderBackground(window);
	RenderUI(sf::Mouse::getPosition(window), window);

	CorrectScroll();
}

// Private

void ScreenManager::RenderBackground(sf::RenderWindow& window) {
	window.setView(window.getDefaultView());

	sf::RectangleShape border({ static_cast<float>(window.getSize().x - 20), static_cast<float>(window.getSize().y - 20) });
	border.setPosition({ 10, 10 });
	border.setOutlineThickness(50);
	border.setOutlineColor(sf::Color::Black);
	border.setFillColor(sf::Color::Transparent);

	sf::RectangleShape border2({ static_cast<float>(window.getSize().x - 60), static_cast<float>(window.getSize().y - 60) });
	border2.setPosition({ 30, 30 });
	border2.setOutlineThickness(50);
	border2.setOutlineColor(sf::Color(0, 0, 0, 100));
	border2.setFillColor(sf::Color::Transparent);

	sf::RectangleShape border3({ static_cast<float>(window.getSize().x - 100), static_cast<float>(window.getSize().y - 100) });
	border3.setPosition({ 50, 50 });
	border3.setOutlineThickness(100);
	border3.setOutlineColor(sf::Color(0, 0, 0, 50));
	border3.setFillColor(sf::Color::Transparent);

	sf::FloatRect rect = sf::FloatRect(
		{ scrollView.getViewport().position.x * window.getSize().x, scrollView.getViewport().position.y * window.getSize().y },
		{ scrollView.getViewport().size.x * window.getSize().x, scrollView.getViewport().size.y * window.getSize().y }
	);

	sf::ConvexShape tint1(4);
	tint1.setPoint(0, { rect.position.x - 20, rect.position.y - 20 });
	tint1.setPoint(1, { rect.position.x + rect.size.x + 60, rect.position.y - 20 });
	tint1.setPoint(2, { rect.position.x + rect.size.x + 40, rect.position.y });
	tint1.setPoint(3, { rect.position.x, rect.position.y });
	tint1.setFillColor(sf::Color(255, 255, 255, 75));
	tint1.setOutlineColor(sf::Color::Transparent);

	sf::ConvexShape tint2(4);
	tint2.setPoint(0, { rect.position.x + rect.size.x + 60, rect.position.y - 20 });
	tint2.setPoint(1, { rect.position.x + rect.size.x + 60, rect.position.y + rect.size.y + 20 });
	tint2.setPoint(2, { rect.position.x + rect.size.x + 40, rect.position.y + rect.size.y });
	tint2.setPoint(3, { rect.position.x + rect.size.x + 40, rect.position.y });
	tint2.setFillColor(sf::Color(200, 200, 200, 75));
	tint2.setOutlineColor(sf::Color::Transparent);

	sf::ConvexShape shade1(4);
	shade1.setPoint(0, { rect.position.x + rect.size.x + 60, rect.position.y + rect.size.y + 20 });
	shade1.setPoint(1, { rect.position.x - 20, rect.position.y + rect.size.y + 20 });
	shade1.setPoint(2, { rect.position.x, rect.position.y + rect.size.y });
	shade1.setPoint(3, { rect.position.x + rect.size.x + 40, rect.position.y + rect.size.y });
	shade1.setFillColor(sf::Color(0, 0, 0, 75));
	shade1.setOutlineColor(sf::Color::Transparent);

	sf::ConvexShape shade2(4);
	shade2.setPoint(0, { rect.position.x - 20, rect.position.y + rect.size.y + 20 });
	shade2.setPoint(1, { rect.position.x - 20, rect.position.y - 20 });
	shade2.setPoint(2, { rect.position.x, rect.position.y });
	shade2.setPoint(3, { rect.position.x, rect.position.y + rect.size.y });
	shade2.setFillColor(sf::Color(50, 50, 50, 75));
	shade2.setOutlineColor(sf::Color::Transparent);

	double totalSales = 0;
	for (Item* item : items) {
		totalSales += item->GetTotal();
	}
	sf::Text total(font, std::format("TOTAL: {0}${1:.2f}",(totalSales < 0) ? "-" : "", std::abs(totalSales)));
	total.setCharacterSize(30);
	total.setPosition({700, 125});

	sf::ConvexShape titleBg(4);
	titleBg.setPoint(0, { 0, 0 });
	titleBg.setPoint(1, { 400, 0 });
	titleBg.setPoint(2, { 500, 70 });
	titleBg.setPoint(3, { 0, 70 });
	titleBg.setFillColor(sf::Color(66, 66, 66));
	titleBg.setOutlineColor(sf::Color::Transparent);

	sf::ConvexShape titleTint(3);
	titleTint.setPoint(0, { 0, 0 });
	titleTint.setPoint(1, { 400, 0 });
	titleTint.setPoint(2, { 500, 70 });
	titleTint.setFillColor(sf::Color(255, 255, 255, 50));
	titleTint.setOutlineColor(sf::Color::Transparent);

	sf::Text title(font, "SALE TRACKER");
	title.setCharacterSize(60);
	title.setStyle(sf::Text::Bold);
	title.setPosition({ 5, 0 });

	sf::Sprite sprite(logo);
	sprite.setScale({ 0.25f, 0.25f });
	sprite.setPosition({ 62, 250 });

	sf::Sprite sprite2(logo);
	sprite2.setScale({ 0.25f, 0.25f });
	sprite2.setPosition({ 910, 250 });

	window.clear(sf::Color(94, 85, 105));
	window.draw(border);
	window.draw(border2);
	window.draw(border3);
	window.draw(tint1);
	window.draw(tint2);
	window.draw(shade1);
	window.draw(shade2);
	window.draw(total);
	window.draw(titleBg);
	window.draw(titleTint);
	window.draw(title);
	window.draw(sprite);
	window.draw(sprite2);

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
	float length = 290;
	for (int i = 0; i < static_cast<int>(items.size() - 4); ++i) {
		length -= length / (i + 4);
	}
	bar.SetSize(bar.GetSize().x, length);
	bar.Render(window);
	if (bar.IsPressed(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), mousePos.x, mousePos.y)) {
		bar.Press();
		float distance = -static_cast<float>(items.size() - 4.5) * 70;
		scroll = distance * bar.GetScrollPercent();
	}
	else
		bar.SetPosition(bar.GetPosition().x, -(this->scroll / ((items.size() - 4.25) * 70)) * (300 - bar.GetSize().y) + 180);

	// RENDER ITEM WINDOW
	//_____________________________________________________
	sf::FloatRect rect = sf::FloatRect(
		{ scrollView.getViewport().position.x * window.getSize().x, scrollView.getViewport().position.y * window.getSize().y },
		{ scrollView.getViewport().size.x * window.getSize().x, scrollView.getViewport().size.y * window.getSize().y }
	);
	sf::RectangleShape shape = sf::RectangleShape({ rect.size.x, rect.size.y });
	shape.setPosition({ rect.position.x, rect.position.y });
	shape.setFillColor(sf::Color(0, 0, 0, 150));
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

bool ScreenManager::MouseInScrollWindow(sf::Vector2i mousePos, sf::RenderWindow& window) {
	sf::FloatRect rect = scrollView.getViewport();
	return (mousePos.x >= rect.position.x * window.getSize().x && mousePos.x <= (rect.position.x + rect.size.x) * window.getSize().x)
		&& (mousePos.y >= rect.position.y * window.getSize().y && mousePos.y <= (rect.position.y + rect.size.y) * window.getSize().y);
}

void ScreenManager::CorrectScroll() {
	if (items.size() > 4) {
		int maxScroll = 70 * static_cast<int>((items.size() - 4)) - 30;
		if (scrollTime >= 35 && prevScroll == scroll) {
			if (-scroll < 0)
				scroll -= scroll / 50;
			else if (-scroll > maxScroll)
				scroll -= (maxScroll + scroll) / 50;
			prevScroll = scroll;
		}
		else if (prevScroll == scroll) {
			scrollTime++;
		}
		else {
			scrollTime = 0;
			prevScroll = scroll;
		}
	}

}