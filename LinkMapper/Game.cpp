#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1280U, 720U, 32U }, "LinkMapper" },
	toolbar{ &m_window, 200 }
{
	sf::Image image;
	image.loadFromFile("ASSETS//ICONS//linkmapper.png");
	m_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	m_view.reset({0, 0, (float)m_window.getSize().x, (float)m_window.getSize().y });
	m_viewPos = { m_view.getSize().x / 2.0f, m_view.getSize().y / 2.0f };

	currentMap_t.loadFromFile("ASSETS//IMAGES//test.png");
	currentMap_s.setTexture(currentMap_t);

	m_window.setView(m_view);

	initialize();
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_window.close();
		}

		if (sf::Event::KeyPressed == newEvent.type)
		{
			if (newEvent.key.code == sf::Keyboard::LControl)
			{
				ctrl_held = true;
			}

			if (newEvent.key.code == sf::Keyboard::S && ctrl_held)
			{
				MessageBoxA(NULL, "Saved Sucessfully", "LinkMapper", MB_OK);
			}

			if (newEvent.key.code == sf::Keyboard::W || newEvent.key.code == sf::Keyboard::Up)
			{
				m_viewPos.y -= 10;
			}

			if (newEvent.key.code == sf::Keyboard::S || newEvent.key.code == sf::Keyboard::Down)
			{
				m_viewPos.y += 10;
			}

			if (newEvent.key.code == sf::Keyboard::A || newEvent.key.code == sf::Keyboard::Left)
			{
				m_viewPos.x -= 10;
			}

			if (newEvent.key.code == sf::Keyboard::D || newEvent.key.code == sf::Keyboard::Right)
			{
				m_viewPos.x += 10;
			}

		}

		if (sf::Event::KeyReleased == newEvent.type)
		{
			if (newEvent.key.code == sf::Keyboard::LControl)
			{
				ctrl_held = false;
			}
		}

		if (sf::Event::MouseWheelMoved == newEvent.type)
		{

			if (newEvent.mouseWheel.delta > 0)
				zoom = 0.9f;
			else if (newEvent.mouseWheel.delta < 0)
				zoom = 1.1f;
			else
				return;
			m_view.zoom(zoom);
			std::cout << zoom << std::endl;
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	toolbar.update();
}

void Game::render()
{
	m_window.clear(sf::Color::White);

	//Map
	m_window.setView(m_view);
	//m_view.reset({ 0, 0, (float)m_window.getSize().x, (float)m_window.getSize().y });
	m_view.setCenter(m_viewPos);
	m_window.draw(currentMap_s);

	

	//UI
	m_window.setView(m_window.getDefaultView());
	toolbar.render();

	
	m_window.display();
}

void Game::initialize()
{
	toolbar.addButton("file");
	toolbar.addButton("edit");
	toolbar.addButton("tools");
	toolbar.addButton("explorer");
	toolbar.getButton("file").ribbon.addButton("save", []() { MessageBoxA(NULL, "Saved Sucessfully", "LinkMapper", MB_OK); });
	toolbar.getButton("file").ribbon.addButton("save as", []() { MessageBoxA(NULL, "Saved Sucessfully", "LinkMapper", MB_OK); });
	toolbar.getButton("file").ribbon.addButton("exit", []() { });
	toolbar.getButton("edit").ribbon.addButton("zoom in", [=]() { 
		zoom = 0.9f;
		m_view.zoom(zoom); 
	});
	toolbar.getButton("edit").ribbon.addButton("zoom out", [=]() {
		zoom = 1.1f;
		m_view.zoom(zoom);
	});
	toolbar.getButton("edit").ribbon.addButton("preferences", []() {});
	toolbar.getButton("edit").ribbon.addButton("project", []() {});

}
