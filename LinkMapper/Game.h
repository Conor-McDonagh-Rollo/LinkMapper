#pragma once
#define WIN32_LEAN_AND_MEAN
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <fstream>
#include "Toolbar.h"

class Game
{
public:
	Game();
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void initialize();

	sf::RenderWindow m_window; 
	sf::View m_view;
	sf::Vector2f m_viewPos;
	float zoom = 0.0f;

	sf::Texture currentMap_t;
	sf::Sprite currentMap_s;


	//file stream
	std::ifstream file; // read only

	//key checking
	bool ctrl_held = false;

	//classes
	Toolbar toolbar;

};

