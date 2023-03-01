#include "Toolbar.h"
sf::Font* Button::font = nullptr;
sf::RenderWindow* Button::window = nullptr;

void Toolbar::initialize()
{
	addButton("file");
	addButton("edit");
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
