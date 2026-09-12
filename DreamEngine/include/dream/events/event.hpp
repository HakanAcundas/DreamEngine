#pragma once
#include <string>

enum struct EventType
{
	KeyPressedEvent,
	KeyReleasedEvent,

	MouseButtonPressedEvent,
	MouseButtonReleasedEvent,
	MouseMovedEvent
};

class Event
{
public:
	virtual ~Event() = default;
	virtual EventType get_type() const = 0;

	std::string to_string(EventType& et)
	{
		std::string st;
		switch (et)
		{
		case EventType::KeyPressedEvent:
			st = "KeyPressedEvent";
			break;
		case EventType::KeyReleasedEvent:
			st = "KeyReleasedEvent";
			break;
		case EventType::MouseButtonPressedEvent:
			st = "MouseButtonPressedEvent";
			break;
		case EventType::MouseButtonReleasedEvent:
			st = "MouseButtonReleasedEvent";
			break;
		case EventType::MouseMovedEvent:
			st = "MouseMovedEvent";
			break;
		}

		return st;
	}

private:
	EventType etype;
	std::string st;
};

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(int key) : key(key) { }

	EventType get_type() const override
	{
		return EventType::KeyPressedEvent;
	}

private:
	int key;
	const EventType etype = EventType::KeyPressedEvent;
};

class KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(int key) : key(key) { }

	EventType get_type() const override
	{
		return EventType::KeyReleasedEvent;
	}

private:
	int key;
	const EventType etype = EventType::KeyReleasedEvent;
};

class MouseButtonPressedEvent : public Event
{
public:
	MouseButtonPressedEvent(int button) : button(button) { }

	EventType get_type() const override
	{
		return EventType::MouseButtonPressedEvent;
	}

private:
	int button;
	const EventType etype = EventType::MouseButtonPressedEvent;
};

class MouseButtonReleasedEvent : public Event
{
public:
	MouseButtonReleasedEvent(int button) : button(button) { }

	EventType get_type() const override
	{
		return EventType::MouseButtonReleasedEvent;
	}

private:
	int button;
	const EventType etype = EventType::MouseButtonReleasedEvent;
};

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(int x, int y) : x(x), y(y) { }

	EventType get_type() const override
	{
		return EventType::MouseMovedEvent;
	}

private:
	int x, y;
	const EventType etype = EventType::MouseMovedEvent;
};
