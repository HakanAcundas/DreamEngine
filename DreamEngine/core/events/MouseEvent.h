#pragma once
#include "Event.h"
#include <glm/glm.hpp>
#include <sstream>

namespace dream {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
		inline EventType GetEventType() const override { return Event::EventType::MOUSE_MOVED; }
		static EventType GetStaticType() { return Event::EventType::MOUSE_MOVED; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }
		inline EventType GetEventType() const override { return Event::EventType::MOUSE_SCROLLED; }
		static EventType GetStaticType() { return Event::EventType::MOUSE_SCROLLED; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	protected:
		int m_Button;
		MouseButtonEvent(int button)
			: m_Button(button) {}
	public:
		inline const int GetButton() const { return m_Button; }
	};

	class MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		inline EventType GetEventType() const override { return Event::EventType::MOUSE_PRESSED; }
		static EventType GetStaticType() { return Event::EventType::MOUSE_PRESSED; }
	};

	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		inline EventType GetEventType() const override { return Event::EventType::MOUSE_RELEASED; }
		static EventType GetStaticType() { return Event::EventType::MOUSE_RELEASED; }
	};
}
