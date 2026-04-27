#include "ScreenManager.h"

// Public


ScreenManager::ScreenManager() :
	items(std::vector<Item*>()),
	add(items, Properties(230, 90, 200, 50, sf::Color(54, 176, 46)), "ADD ITEM", "Assets\\Fonts\\Shelten.ttf"),
	bar(Properties(856, 180, 40, 300, sf::Color(18, 18, 18)),
		Properties(861, 185, 30, 50, sf::Color(166, 166, 166)))
{
	// INITIALIZE SCROLLING
	// _____________________________________________________

	// Initialize variables utilized for managing the scroll view and scrolling behavior. 
	scrollView.setSize({ 700, 330 }); 
	scrollView.setViewport(sf::FloatRect({ 0.2f, 0.3f }, { 0.565f, 0.5f }));
	scroll = 0;
	prevScroll = 0;


	// LOAD FONT & LOGO
	// _____________________________________________________

	// Attempt to load the font from the specified file path. 
	// If the font fails to load, catch the exception and print an error message to the standard error stream.
	std::string font = "Assets\\Fonts\\Shelten.ttf";
	try {
		if (!this->font.openFromFile(font))
			throw "FAILED TO LOAD FONT:\t" + font;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	// Attempt to load the logo texture from the specified file path. 
	// If the texture fails to load, catch the exception and print an error message to the standard error stream.
	std::string logoPath = "Assets\\Sprites\\gift_logo.png";
	try {
		if (!logo.loadFromFile(logoPath))
			throw "FAILED TO LOAD TEXTURE:\t" + logoPath;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	// Seed the random number generator with the current time to ensure that any subsequent calls to random functions produce different sequences of random numbers each time the program is run.
	std::srand(static_cast<unsigned int>(time(NULL))); 
}

ScreenManager::~ScreenManager() noexcept {
	// Clean up dynamically allocated memory for items to prevent memory leaks. 
	for (Item* item : items) {
		delete item;
	}
}

void ScreenManager::Scroll(float scroll, sf::RenderWindow& window) {
	// Adjust the scroll position by the specified amount.
	if (MouseInScrollWindow(sf::Mouse::getPosition(window), window) && items.size() > 4)
		this->scroll += scroll * 10;
}

void ScreenManager::EditItem(char character) {
	// Iterate through all items in the vector and call their Edit method, passing the specified character as an argument. 
	for (Item* item : items) {
		item->Edit(character);
	}
}

void ScreenManager::Render(sf::RenderWindow& window) {
	// If there are fewer than 5 items, reset the scroll position to 0 and set the scroll bar position to 185. 
	if (items.size() < 5) {
		scroll = 0;
		bar.SetPosition(185);
	}

	RenderBackground(window); // Render the background elements of the screen, including any static visuals or decorations that form the backdrop for the user interface.
	RenderUI(sf::Mouse::getPosition(window), window); // Render the user interface elements, potentially using the current mouse position for interaction. This includes rendering buttons, scroll bars, and any interactive components that allow the user to interact with the application.

	CorrectScroll(); // Adjust the scroll position to ensure it stays within valid bounds.
}

// Private

void ScreenManager::RenderBackground(sf::RenderWindow& window) const {
	// RENDER BACKGROUND ELEMENTS
	// _____________________________________________________

	// Set the view of the window to the default view, which is typically a view that covers the entire render target. 
	// This ensures that subsequent drawing operations are performed in the context of the default coordinate system and viewport.
	window.setView(window.getDefaultView());
	window.clear(sf::Color(94, 85, 105));

	// Draw background elements such as borders, title, and logos. 
	sf::FloatRect rect = sf::FloatRect(
		{ scrollView.getViewport().position.x * 1120, scrollView.getViewport().position.y * 600 },
		{ scrollView.getViewport().size.x * 1120, scrollView.getViewport().size.y * 600 }
	);
	RenderIndentBorder(window, rect, 20);
	RenderBorder(window, { 10, 10 }, { 1100, 580 }, sf::Color::Black, 50);
	RenderTitle(window);
	RenderSprite(window, logo, { 62, 250 }, { 0.25f, 0.25f });
	RenderSprite(window, logo, { 922, 250 }, { 0.25f, 0.25f });

	// RENDER TOTAL
	// _____________________________________________________

	// Calculate the total sales by iterating through all items and summing their total values. 
	// The total is then displayed as text on the screen.
	double totalSales = 0;
	for (Item* item : items) {
		totalSales += item->GetTotal();
	}
	sf::Text total(font, std::format("TOTAL: {0}${1:.2f}",(totalSales < 0) ? "-" : "", std::abs(totalSales)));
	total.setCharacterSize(30);
	total.setPosition({700, 120});
	total.setOutlineThickness(3);
	total.setOutlineColor(sf::Color::Black);
	window.draw(total); // Draw the total sales text on the window at the specified position.

}

void ScreenManager::RenderUI(sf::Vector2i mousePos, sf::RenderWindow& window) {

	// RENDER ADD BUTTON
	//_____________________________________________________

	// Convert the mouse position from pixel coordinates to world coordinates using the default view of the window. 
	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, window.getDefaultView());
	add.Render(window);
	// Check if the add button is being pressed by the user. 
	if (add.IsPressed(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), static_cast<int>(worldPos.x), static_cast<int>(worldPos.y)))
		add.Press();

	// RENDER SCROLL BAR
	//_____________________________________________________

	// Calculate the length of the scroll bar based on the number of items in the list.
	float length = 290;
	for (int i = 0; i < static_cast<int>(items.size() - 4); ++i) {
		length -= length / (i + 4);
	}
	bar.SetSize(bar.GetSize().x, length);
	bar.Render(window);
	// Check if the scroll bar is being pressed by the user. 
	if (items.size() > 4 && bar.IsPressed(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), static_cast<int>(worldPos.x), static_cast<int>(worldPos.y))) {
		bar.Press();
		float distance = -static_cast<float>(items.size() - 4.5) * 70;
		scroll = distance * bar.GetScrollPercent();
	}
	else
		bar.SetPosition(static_cast<float>(-(this->scroll / ((items.size() - 4.5) * 70)) * (300 - bar.GetSize().y) + 180));

	// RENDER ITEM WINDOW
	//_____________________________________________________

	// Render a semi-transparent rectangle as the background for the item window.
	sf::FloatRect rect = sf::FloatRect(
		{ scrollView.getViewport().position.x * 1120, scrollView.getViewport().position.y * 600 },
		{ scrollView.getViewport().size.x * 1120, scrollView.getViewport().size.y * 600 }
	);
	sf::RectangleShape shape = sf::RectangleShape({ rect.size.x, rect.size.y });
	shape.setPosition({ rect.position.x, rect.position.y });
	shape.setFillColor(sf::Color(0, 0, 0, 150));
	window.draw(shape); // Draw the semi-transparent rectangle on the window to serve as the background for the item display area.

	// RENDER ITEMS
	//_____________________________________________________	

	// Set the view of the window to the scroll view, which allows for rendering the items in a coordinate space that can be scrolled.
	window.setView(scrollView);
	worldPos = window.mapPixelToCoords(mousePos, scrollView);

	// If there are items in the list, iterate through each item and render and interact with it on the window.
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

void ScreenManager::RenderBorder(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Color color, int thickness) const {
	// Render a border around a specified area by drawing multiple rectangles with decreasing size and increasing transparency. 
	sf::RectangleShape border;
	for (int i = 0; i < 3; ++i) {
		border.setSize({ size.x - i * 40, size.y - i * 40 });
		border.setPosition({ position.x + i * 20, position.y + i * 20 });
		border.setOutlineThickness(50);
		border.setOutlineColor(sf::Color(color.r, color.b, color.g, 255 - i * 100));
		border.setFillColor(sf::Color::Transparent);
		window.draw(border); // Draw the current layer of the border on the window.
	}
}

void ScreenManager::RenderIndentBorder(sf::RenderWindow& window, sf::FloatRect rect, int indent) const {
	// Create an array of colors with varying levels of transparency to be used for rendering the indent border.
	sf::Color colors[4] = { sf::Color(255, 255, 255, 75), sf::Color(200, 200, 200, 75),
		sf::Color(20, 20, 20, 75), sf::Color(50, 50, 50, 75) };	
	// Define an array of points that represent the vertices of the indent border. 
	sf::Vector2f points[16] = {
		{ rect.position.x - indent, rect.position.y - indent },
		{ rect.position.x + rect.size.x + 60, rect.position.y - indent },
		{ rect.position.x + rect.size.x + 60 - indent, rect.position.y },
		{ rect.position.x, rect.position.y },

		{ rect.position.x + rect.size.x + 60, rect.position.y - indent },
		{ rect.position.x + rect.size.x + 60, rect.position.y + rect.size.y + indent },
		{ rect.position.x + rect.size.x + 60 - indent, rect.position.y + rect.size.y },
		{ rect.position.x + rect.size.x + 60 - indent, rect.position.y },

		{ rect.position.x + rect.size.x + 60, rect.position.y + rect.size.y + indent },
		{ rect.position.x - indent, rect.position.y + rect.size.y + indent },
		{ rect.position.x, rect.position.y + rect.size.y },
		{ rect.position.x + rect.size.x + 60 - indent, rect.position.y + rect.size.y },

		{ rect.position.x - indent, rect.position.y + rect.size.y + indent },
		{ rect.position.x - indent, rect.position.y - indent },
		{ rect.position.x, rect.position.y },
		{ rect.position.x, rect.position.y + rect.size.y }
	};

	// Render the indent border by drawing four convex shapes, each representing a layer of the border. 
	sf::ConvexShape edge(4);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			edge.setPoint(j, points[j + i * 4]);
		}
		edge.setFillColor(colors[i]);
		edge.setOutlineColor(sf::Color::Transparent);
		window.draw(edge); // Draw the current layer of the indent border on the window.
	}
}

void ScreenManager::RenderTitle(sf::RenderWindow& window) const {
	sf::ConvexShape titleBg(4);
	titleBg.setPoint(0, { 0, 0 });
	titleBg.setPoint(1, { 400, 0 });
	titleBg.setPoint(2, { 500, 70 });
	titleBg.setPoint(3, { 0, 70 });
	titleBg.setFillColor(sf::Color(66, 66, 66));
	titleBg.setOutlineColor(sf::Color::Transparent);
	window.draw(titleBg); // Draw the background shape for the title.

	sf::ConvexShape titleT(5);
	titleT.setPoint(0, { 0, 0 });
	titleT.setPoint(1, { 400, 0 });
	titleT.setPoint(2, { 500, 70 });
	titleT.setPoint(3, { 400, 20 });
	titleT.setPoint(4, { 0, 20 });
	titleT.setFillColor(sf::Color(255, 255, 255, 50));
	titleT.setOutlineColor(sf::Color::Transparent);
	window.draw(titleT); // Draw an additional shape for the title.

	sf::Text title(font, "SALE TRACKER");
	title.setPosition({ 5, 0 });
	title.setCharacterSize(60);
	title.setStyle(sf::Text::Bold);
	title.setOutlineThickness(5);
	title.setOutlineColor(sf::Color::Black);
	window.draw(title); // Draw the title text on the window using the specified font, character size, and style. 
}

void ScreenManager::RenderSprite(sf::RenderWindow& window, sf::Texture texture, sf::Vector2f position, sf::Vector2f scale) const {
	// Render a background rectangle for the sprite, positioned and sized based on the provided position and scale parameters. 
	sf::RectangleShape bg({ 440 * scale.x, 420 * scale.y });
	bg.setPosition({ position.x + 55 * scale.x, position.y + 120 * scale.y });
	bg.setFillColor(sf::Color(255, 255, 255, 160));
	window.draw(bg); // Draw the background rectangle for the sprite on the window.

	// Render the sprite using the specified texture, position, and scale.
	sf::Sprite sprite(texture);
	sprite.setScale(scale);
	sprite.setPosition(position);
	window.draw(sprite); // Draw the sprite on the window using the specified texture, scale, and position. 
}

bool ScreenManager::MouseInScrollWindow(sf::Vector2i mousePos, sf::RenderWindow& window) const {
	// Check if the mouse cursor is within the bounds of the scrollable area defined by the scroll view's viewport. 
	sf::FloatRect rect = scrollView.getViewport();
	return (mousePos.x >= rect.position.x * window.getSize().x && mousePos.x <= (rect.position.x + rect.size.x) * window.getSize().x)
		&& (mousePos.y >= rect.position.y * window.getSize().y && mousePos.y <= (rect.position.y + rect.size.y) * window.getSize().y);
}

void ScreenManager::CorrectScroll() {
	// Adjust the scroll position to ensure it stays within valid bounds based on the number of items and the size of the scrollable area. 
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