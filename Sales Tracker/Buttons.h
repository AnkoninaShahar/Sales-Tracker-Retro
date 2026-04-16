#pragma once
#include <vector>

#include "Button.h"
#include "Item.h"

class Add : public Button
{
public:
	Add(std::vector<Item>* list = nullptr, float x = 0, float y = 0, float width = 0, float height = 0, std::string text = "") :
		list(list), Button(x, y, width, height, sf::Color::Green, text) {}

	void Press() override {
		Item blank(list->size() * 20, 100, 40, 40);
		list->push_back(blank);
	}

private:
	std::vector<Item>* list = nullptr;
};


class Remove : public Button
{
public:
	Remove(std::vector<Item>* list = nullptr, int index = 0, float x = 0, float y = 0, float width = 0, float height = 0, std::string text = "") :
		list(list), index(index), Button(x, y, width, height, sf::Color::Red, text) {}

	void Press() override {
		if (list)
			list->erase(list->begin() + index);
	}
private:
	std::vector<Item>* list = nullptr;
	int index = index;
};


class Sell : public Button
{
public:
	using Button::Button;

	void Press() override {
		item->Sell();
	}

	void SetItem(Item* item) {
		this->item = item;
	}

private:
	Item* item = nullptr;
};


class Unsell : public Button
{
public:
	using Button::Button;

	void Press() override {
		item->Unsell();
	}

	void SetItem(Item* item) {
		this->item = item;
	}

private:
	Item* item = nullptr;
};

