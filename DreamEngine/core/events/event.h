#pragma once
#include <string>
#include <functional>

namespace dream {

	class Event
	{
	public:
		enum class EventType
		{
			KEY_PRESSED = 0,
			KEY_RELEASED,

			MOUSE_PRESSED,
			MOUSE_RELEASED,
			MOUSE_MOVED,
			MOUSE_SCROLLED,

			WINDOW_RESIZE
		};

		bool handled = false;
	public:
		virtual EventType GetEventType() const = 0;
		virtual std::string ToString() const
		{
			return "Event: ";
		}

		static std::string TypeToString(EventType type)
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

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
