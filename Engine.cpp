#include "Engine.hpp"

Engine::Engine(EventEngine* _eventEngine) {

	eventEngine = _eventEngine;	
}

Engine::~Engine() {

}

void Engine::attachEngine(std::string _name, Engine* _engine) {

	engines[_name] = _engine;
}