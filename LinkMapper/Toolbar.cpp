#include "Toolbar.h"
sf::Font* Button::font = nullptr;
sf::RenderWindow* Button::window = nullptr;

sf::Font* Ribbon::font = nullptr;
sf::RenderWindow* Ribbon::window = nullptr;

float Button::width = 100.0f;
float Ribbon::width = 100.0f;

void Toolbar::initialize()
{
	Button::width = width;
	Ribbon::width = width;
}

void Toolbar::render()
{
	m_window->draw(toolbar_rect);

	for (auto& kv : buttons) {
		kv.second.render();
	}
}

void Toolbar::update()
{
	for (auto& kv : buttons) {
		kv.second.update();
	}
}

void Toolbar::addButton(std::string name)
{
	Button b(name, amountOfBtns);
	buttons.emplace(name, b);

	amountOfBtns++;
}
