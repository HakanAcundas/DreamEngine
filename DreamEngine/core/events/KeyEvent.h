#pragma once

#include "Event.h"


namespace dream {

		class KeyEvent : public Event
		{
		protected:
			int m_KeyCode;
			int m_Count;
		public:
			KeyEvent(int keycode)
				: m_KeyCode(keycode) {}

			inline int GetKeyCode() const { return m_KeyCode; }
			inline static int GetStaticType() { return (int)Event::Type::KEY_PRESSED | (int)Event::Type::KEY_RELEASED; }
		};

		class KeyPressedEvent : public KeyEvent
		{
		private:
			int m_Repeat;
		public:
			KeyPressedEvent(int keycode, bool repeat)
				: KeyEvent(keycode), m_Repeat(repeat) {}

			inline int GetRepeat() const { return m_Repeat; }
			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_Repeat << " repeats)";
				return ss.str();
			}
			inline static Type GetStaticType() { return Event::Type::KEY_PRESSED; }
		};

		class KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(int keycode)
				: KeyEvent(keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyReleasedEvent: " << m_KeyCode;
				return ss.str();
			}
			inline static Type GetStaticType() { return Event::Type::KEY_RELEASED; }
		};

	}
