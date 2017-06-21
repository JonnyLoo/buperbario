#include <mutex>
#include <vector>

#include "GameEngine.hpp"
#include "GraphicsEngine.hpp"
#include "SoundEngine.hpp"
#include "EventEngine.hpp"
#include "EventListener.hpp"

class Game {

public:
	Game();
	~Game();
	void run();
	void stop();

private:
	bool running;
	std::mutex running_mutex;

	GameEngine *gEngine;
	GraphicsEngine *gfxEngine;
	SoundEngine *sEngine;
	EventEngine *eEngine;
	std::vector<EventListener*> listeners;
};