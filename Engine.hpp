#include <map>
#include <iostream>
#include <queue>

#include "EventEngine.hpp"

class Game;

class Engine {

public:
	Engine(EventEngine*);
	virual ~Engine();

	void attachEngine(std::string _name, Engine* _engine);
	virtual void frame() = 0;

protected:
	EventEngine* eventEngine;
	std::map <std::string, Engine*> engines;
	std::vector<EventListener*> createdListeners;

private:
	virtual void createListeners() = 0;
};