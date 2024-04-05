#pragma once
#include <string>
#include <functional>

namespace dream {

	class Event
	{
	public:
		enum class Type
		{
			KEY_PRESSED = 0,
			KEY_RELEASED,

			MOUSE_PRESSED,
			MOUSE_RELEASED,
			MOUSE_MOVED,
			MOUSE_SCROLLED,

			WINDOW_RESIZE
		};
	protected:
		bool m_Handled;
		Type m_Type;
	public:
		inline Type GetType() const { return m_Type; }
		inline bool IsHandled() const { return m_Handled; }

		virtual std::string ToString() const
		{
			return "Event: ";
		}

		static std::string TypeToString(Type type)
		{
			switch (type)
			{
			case Type::KEY_PRESSED:
				return "KEY_PRESSED";
			case Type::KEY_RELEASED:
				return "KEY_RELEASED";
			case Type::MOUSE_PRESSED:
				return "MOUSE_PRESSED";
			case Type::MOUSE_RELEASED:
				return "MOUSE_RELEASED";
			case Type::MOUSE_MOVED:
				return "MOUSE_MOVED";
			}
			return "INVALID";
		}
	};
}
