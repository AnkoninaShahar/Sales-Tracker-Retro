#pragma once
#include <vector>

#include "Button.h"
#include "Item.h"

class Remove : public Button
{
public:
	Remove(std::vector<Item*>& list, Properties properties = Properties(), std::string text = "") :
		list(list), Button(properties, text) {}

	~Remove() {
		if (item != nullptr) {
			item = nullptr;
			delete item;
		}
	}

	void Press() override {
		list.erase(std::remove(list.begin(), list.end(), item), list.end());
		item = nullptr;
		delete item;
	}

	void SetItem(Item* item) {
		this->item = item;
	}

private:
	std::vector<Item*>& list;
	Item* item = nullptr;
};


class Sell : public Button
{
public:
	using Button::Button;

	~Sell() {
		if (item != nullptr) {
			item = nullptr;
			delete item;
		}
	}

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

	~Unsell() {
		if (item != nullptr) {
			item = nullptr;
			delete item;
		}
	}

	void Press() override {
		item->Unsell();
	}

	void SetItem(Item* item) {
		this->item = item;
	}

private:
	Item* item = nullptr;
};

class Add : public Button
{
public:
	Add(std::vector<Item*>& list, Properties properties = Properties(), std::string text = "") :
		list(list), Button(properties, text) {
	}

	void Press() override {
		Properties itemProps(properties.x, 0, 700, 60);
		Properties sellProps(5, 5, 50, 50, sf::Color::Green);
		Properties unsellProps(55, 5, 50, 50, sf::Color::Red);
		Properties removeProps(640, 5, 50, 50, sf::Color::Red);

		Item* blank = new Item(itemProps, 9.95, "BLANK");

		Sell* sell = new Sell(sellProps);
		sell->SetItem(blank);
		Unsell* unsell = new Unsell(unsellProps);
		unsell->SetItem(blank);
		Remove* remove = new Remove(list, removeProps);
		remove->SetItem(blank);

		blank->SetButtons(sell, unsell, remove);

		list.push_back(blank);
	}

private:
	std::vector<Item*>& list;
};
