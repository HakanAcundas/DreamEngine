#pragma once
#include "event.h"
#include <glm/glm.hpp>
#include <sstream>

namespace dream {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_mouse_x(x), m_mouse_y(y) {}

		inline float get_x() const { return m_mouse_x; }
		inline float get_y() const { return m_mouse_y; }
		inline EventType get_event_type() const override { return Event::EventType::MOUSE_MOVED; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouse_x << ", " << m_mouse_y;
			return ss.str();
		}
	private:
		float m_mouse_x, m_mouse_y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float offset_x, const float offset_y)
			: m_offset_x(offset_x), m_offset_y(offset_y) {}

		float get_offset_x() const { return m_offset_x; }
		float get_offset_y() const { return m_offset_y; }
		inline EventType get_event_type() const override { return Event::EventType::MOUSE_SCROLLED; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << get_offset_x() << ", " << get_offset_y();
			return ss.str();
		}

	private:
		float m_offset_x, m_offset_y;
	};

	class MouseButtonEvent : public Event
	{
	protected:
		int m_button;
		MouseButtonEvent(int button)
			: m_button(button) {}
	public:
		inline const int get_button() const { return m_button; }
	};

	class MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}
		inline EventType get_event_type() const override { return Event::EventType::MOUSE_PRESSED; }
	};

	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
		inline EventType get_event_type() const override { return Event::EventType::MOUSE_RELEASED; }
	};
}
