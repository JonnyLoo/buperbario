#include "gui.h"

using namespace sf;

Menu::Menu() {

	RenderWindow menu;
	bool decision;
}

void Menu::load() {

	menu = RenderWindow(VideoMode(800, 600), "Menu");

}

bool Menu::getDecision() {

	return decision;
}

void Menu::close() {

	menu.close();
}