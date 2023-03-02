#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <functional>
#include <vector>

struct RibbonButton
{
	std::function<void()> callback;
	sf::Text text;
	sf::RectangleShape bg;
};

struct Ribbon
{
public:
	Ribbon(int num)
	{
		xStartPos = num;
	}

	bool enabled = false;

	void addButton(std::string s, std::function<void()> call)
	{
		RibbonButton btn;
		btn.text.setPosition({ xStartPos * width, yStartPos * 50.0f });
		btn.text.setFont(*font);
		btn.text.setString(s);

		btn.bg.setPosition({ xStartPos * width, yStartPos * 50.0f });
		btn.bg.setFillColor(sf::Color(25, 25, 25, 115));
		btn.bg.setSize(sf::Vector2f(width, 40.0f));

		btn.callback = call;

		ribbonBtns.emplace_back(btn);
		yStartPos++;
	}

	void update()
	{
		for (RibbonButton& b : ribbonBtns)
		{
			if (b.bg.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
			{
				b.bg.setFillColor(sf::Color(25, 25, 25, 85));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					b.callback();
				}
			}
			else
			{
				b.bg.setFillColor(sf::Color(25, 25, 25, 115));
			}
		}
	}

	void render()
	{
		for (RibbonButton& b : ribbonBtns)
		{
			window->draw(b.bg);
			window->draw(b.text);
		}
	}

	int size() const { return ribbonBtns.size(); }

	static sf::Font* font;
	static sf::RenderWindow* window;
	static float width;
private:
	int xStartPos;
	int yStartPos = 1;

	std::vector<RibbonButton> ribbonBtns;
};

struct Button
{
public:
	Button() : ribbon{ 0 } {}

	Button(std::string s, int num)
		: ribbon{num}
	{
		text.setPosition({ num * width, 0.0f });
		text.setFont(*font);
		text.setString(s);

		bg.setPosition({ num * width, 0.0f });
		bg.setFillColor(sf::Color(25, 25, 25, 105));
		bg.setSize(sf::Vector2f(width, 40.0f));
	}

	void update()
	{
		if (bg.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
		{
			bg.setFillColor(sf::Color(25, 25, 25, 45));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				ribbon.enabled = true;
			}
		}
		else
		{
			bg.setFillColor(sf::Color(25, 25, 25, 105));
			float height = (ribbon.size() * 50.0f) + 50.0f;
			if (!sf::FloatRect({ bg.getPosition() }, { bg.getGlobalBounds().width, height }).contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					ribbon.enabled = false;
				}
			}
		}

		if (ribbon.enabled)
		{
			ribbon.update();
		}
	}

	void render()
	{
		window->draw(bg);
		window->draw(text);

		if (ribbon.enabled)
		{
			ribbon.render();
		}
	}

	static sf::Font* font;
	static sf::RenderWindow* window;
	static float width;
	Ribbon ribbon;
private:
	sf::Text text;
	sf::RectangleShape bg;
};

class Toolbar
{
public:
	Toolbar(sf::RenderWindow* t_window, float t_width) : m_window(t_window) 
	{
		toolbar_rect.setFillColor(sf::Color(25, 25, 25, 155));
		toolbar_rect.setSize(sf::Vector2f(m_window->getSize().x, 50.0f));
		Button::font = new sf::Font();
		Button::font->loadFromFile("ASSETS//FONTS//ariblk.ttf");
		Button::window = t_window;

		Ribbon::font = new sf::Font();
		Ribbon::font->loadFromFile("ASSETS//FONTS//ariblk.ttf");
		Ribbon::window = t_window;

		width = t_width;
		initialize();
	}
	
	void initialize();
	void render();
	void update();

	void addButton(std::string name);
	Button& getButton(std::string name) { return buttons[name]; }

private:
	sf::RenderWindow* m_window;

	sf::RectangleShape toolbar_rect;
	std::map<std::string, Button> buttons;

	float width;
	int amountOfBtns = 0;
};

