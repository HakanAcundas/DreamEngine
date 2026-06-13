#include "event_dispatcher.hpp"

EventDispatcher::EventDispatcher() { }

void EventDispatcher::listen(const EventType& etype, EventFunction&& function)
{
	listener_map[etype].push_back(function);
}

void EventDispatcher::post(Event& event)
{
	EventType type = event.get_type();
	if (listener_map.find(type) == listener_map.end())
		return;

	auto&& functions = listener_map.at(type);
	for (EventFunction function : functions)
		function(event);
}
