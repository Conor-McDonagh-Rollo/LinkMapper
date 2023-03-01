#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
struct Ribbon
{
	bool enabled = false;
};

struct Button
{
public:
	Button(std::string s, int num)
	{
		text.setPosition({ num * 100.0f, 0.0f });
		text.setFont(*font);
		text.setString(s);

		bg.setPosition({ num * 100.0f, 0.0f });
		bg.setFillColor(sf::Color(25, 25, 25, 105));
		bg.setSize(sf::Vector2f(100.0f, 40.0f));
	}

	void update()
	{
		std::cout << window->mapPixelToCoords(sf::Mouse::getPosition()).x << ", " << window->mapPixelToCoords(sf::Mouse::getPosition()).y << std::endl;
		if (bg.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition())))
		{
			bg.setFillColor(sf::Color(25, 25, 25, 85));
		}
		else
		{
			bg.setFillColor(sf::Color(25, 25, 25, 105));
		}
	}

	void render()
	{
		window->draw(bg);
		window->draw(text);
	}

	static sf::Font* font;
	static sf::RenderWindow* window;
private:
	sf::Text text;
	sf::RectangleShape bg;
};

class Toolbar
{
public:
	Toolbar(sf::RenderWindow* t_window) : m_window(t_window) 
	{
		toolbar_rect.setFillColor(sf::Color(25, 25, 25, 155));
		toolbar_rect.setSize(sf::Vector2f(m_window->getSize().x, 50.0f));
		Button::font = new sf::Font();
		Button::font->loadFromFile("ASSETS//FONTS//ariblk.ttf");
		Button::window = t_window;
		initialize();
	}
	
	void initialize();
	void render();
	void update();

	void addButton(std::string name);

private:
	sf::RenderWindow* m_window;

	sf::RectangleShape toolbar_rect;
	std::map<std::string, Button> buttons;

	int amountOfBtns = 0;
};

