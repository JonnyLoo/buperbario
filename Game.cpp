#include "Game.hpp"

Game::Game() {

	running = true;

	eEngine = new EventEngine();
	gEngine = new GameEngine();
	gfxEngine = new GraphicsEngine();
	sEngine = new SoundEngine();

	CloseRequestListener* closeRequestListener = new CloseRequestListener(this);
	eEngine->addListener("graphics.stop_request", closeRequestListener);
	listeners.push_back(closeRequestListener);
}

Game::~Game() {

	delete gEngine;
	delete gfxEngine;
	delete sEngine;
	for (int i = 0; i < listeners.size(); i++) {

		delete listeners[i];
	}
	delete eEngine;
}

void Game::run() {

	bool isRunning = running;

	sf::Clock clock;

	while(isRunning) {

		gEngine->frame(clock.getElapsedTime().asSeconds());
		clock.restart();
		gfxEngine->frame();
		sEngine->frame();

		running_mutex.lock();
		isRunning = running;
		running_mutex.unlock();

		float framerateLimit = gfxEngine->getFpsLimit();
	}
}

void Game::stop() {

	running_mutex.lock();
	running = false;
	running_mutex.unlock();
}