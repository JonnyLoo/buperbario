#include <string>
#include "Event.hpp"

class EventListener {

public:
	virtual EventListener(){};
	virtual void onEvent(const std::string _eventType, Event* _event) = 0;
}