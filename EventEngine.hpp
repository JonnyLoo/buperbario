#include <map>
#include <queue>
#include <iostream>
#include <string>

#include "KeyboardEvent.hpp"
#include "EventListener.hpp"

class EventEngine {
	
public:
	void addListener(EventListener* _listener);
	void addListener(const std::string _eventName, EventListener* _listener);
	void sendEvent(const std::string _eventType, Event* _event);

private:
	std::map<std::string, std::vector<EventListener*>> specificListeners;
	std::vector<EventListener*> generalListeners;
};