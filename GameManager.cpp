#include "world.h"

using namespace sf;

GameManager::GameManager() {

	RenderWindow w;
	Level l;
	Bario bario;
}

void GameManger::initialize() {

	w = RenderWindow(VideoMode(800, 600), "Buper Bario Burld");
	l.createLevel();
}