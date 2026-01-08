#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include "event.hpp"

class EventDispatcher
{
public:
	using EventFunction = std::function<void(Event&)>;

	EventDispatcher();
	~EventDispatcher() = default;

	void listen(const EventType& etype, EventFunction&& function);
	void post(Event& event);

private:
	std::unordered_map<EventType, std::vector<EventFunction>> listener_map;
};