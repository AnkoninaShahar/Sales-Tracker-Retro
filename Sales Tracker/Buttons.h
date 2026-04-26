#pragma once
#include <vector>

#include "Button.h"
#include "TextBox.h"
#include "Item.h"

class Sale : public Button
{
public:
	Sale(Item* item = nullptr, int amount = 0, Properties properties = Properties(), std::string text = "", std::string fontPath = "Fonts\\Thraex.ttf");
	~Sale() noexcept;

	void Press() override;

private:
	Item* item;
	int amount;
};



class Remove : public Button
{
public:
	Remove(std::vector<Item*>& list, Item* item = nullptr, Properties properties = Properties(), std::string text = "", std::string fontPath = "Fonts\\Thraex.ttf");
	~Remove() noexcept;

	void Press() override;

private:
	std::vector<Item*>& list;
	Item* item;
};



class Add : public Button
{
public:
	Add(std::vector<Item*>& list, Properties properties = Properties(), std::string text = "", std::string fontPath = "Fonts\\Thraex.ttf");

	void Press() override;

private:
	std::vector<Item*>& list;
	std::string fontPath;
};
