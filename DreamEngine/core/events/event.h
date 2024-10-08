#pragma once
#include <string>
#include <functional>

namespace dream {
	

	class Event
	{
	public:
		enum class EventType
		{
			KEY_PRESSED = 1,
			KEY_RELEASED,

			MOUSE_PRESSED,
			MOUSE_RELEASED,
			MOUSE_MOVED,
			MOUSE_SCROLLED,

			WINDOW_RESIZE
		};
		bool handled = false;
	public:
		virtual EventType get_event_type() const = 0;
		virtual std::string to_string() const
		{
			return "Event: ";
		}

		static std::string type_to_string(EventType type)
		{
			switch (type)
			{
			case EventType::KEY_PRESSED:
				return "KEY_PRESSED";
			case EventType::KEY_RELEASED:
				return "KEY_RELEASED";
			case EventType::MOUSE_PRESSED:
				return "MOUSE_PRESSED";
			case EventType::MOUSE_RELEASED:
				return "MOUSE_RELEASED";
			case EventType::MOUSE_MOVED:
				return "MOUSE_MOVED";
			}
			return "INVALID";
		}
	};
}
