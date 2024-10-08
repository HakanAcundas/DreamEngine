#pragma once

#include "event.h"


namespace dream {

		class KeyEvent : public Event
		{
		protected:
			int m_keycode;
			int m_count;
		public:
			KeyEvent(int keycode)
				: m_keycode(keycode) {}

			inline int get_keycode() const { return m_keycode; }
		};

		class KeyPressedEvent : public KeyEvent
		{
		private:
			int m_repeat;
		public:
			KeyPressedEvent(int keycode, bool repeat)
				: KeyEvent(keycode), m_repeat(repeat) {}

			inline int get_repeat() const { return m_repeat; }
			std::string to_string() const override
			{
				std::stringstream ss;
				ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeat << " repeats)";
				return ss.str();
			}
			inline EventType get_event_type() const override { return Event::EventType::KEY_PRESSED; }
		};

		class KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(int keycode)
				: KeyEvent(keycode) {}

			std::string to_string() const override
			{
				std::stringstream ss;
				ss << "KeyReleasedEvent: " << m_keycode;
				return ss.str();
			}
			inline EventType get_event_type() const override { return Event::EventType::KEY_RELEASED; }
		};

	}
