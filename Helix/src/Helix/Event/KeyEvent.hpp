#pragma once

#include "Helix/Event/Base/Event.hpp"
#include "Helix/Input/KeyCode.hpp"

namespace hlx
{
	class KeyEvent : public Event
	{
	public:
		KeyCode getKeyCode() const { return m_keyCode; }

		EVENT_CLASS(Event::Class::Input | Event::Class::Keyboard)

	protected:
		KeyEvent(const KeyCode keyCode)
			: m_keyCode{ keyCode } {}

	private:
		KeyCode m_keyCode;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(const KeyCode keyCode, const unsigned int repeatCount)
			: KeyEvent{ keyCode }, m_repeatCount{ repeatCount } {}

		unsigned int getRepeatCount() const { return m_repeatCount; }

		EVENT_TYPE(Event::Type::KeyPress)
		EVENT_DEBUG("Key Pressed: " << getKeyCode())

	private:
		unsigned int m_repeatCount;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(const KeyCode keyCode)
			: KeyEvent{ keyCode } {}

		EVENT_TYPE(Event::Type::KeyRelease)
		EVENT_DEBUG("Key Released: " << getKeyCode())
	};
}
