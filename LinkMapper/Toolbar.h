#pragma once
#include <SFML/Graphics.hpp>

class Toolbar
{
public:
	Toolbar(sf::RenderWindow* t_window) : m_window(t_window) 
	{
		toolbar_rect.setFillColor(sf::Color(25, 25, 25, 255));
		toolbar_rect.setSize(sf::Vector2f(m_window->getSize().x, 50.0f));
	}
	
	void Draw();

private:
	sf::RenderWindow* m_window;

	sf::RectangleShape toolbar_rect;
};

