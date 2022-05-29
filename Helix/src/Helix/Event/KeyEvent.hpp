#pragma once

#include "Helix/Event/Base/Event.hpp"
#include "Helix/Input/KeyCode.hpp"

namespace hlx
{
	using KeyCode = int;

	class KeyEvent : public Event
	{
	public:
		KeyCode getKeyCode() const { return this->keyCode; }

		EVENT_CLASS(Event::Class::Input | Event::Class::Keyboard)

	protected:
		KeyEvent(const KeyCode keyCode)
			: keyCode{ keyCode } {}

		KeyCode keyCode;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(const KeyCode keyCode, const uint16_t repeatCount)
			: KeyEvent{ keyCode }, repeatCount{ repeatCount } {}

		uint16_t getRepeatCount() const { return repeatCount; }

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed: " << keyCode;
			return ss.str();
		}

		EVENT_TYPE(Event::Type::KeyPress)

	private:
		uint16_t repeatCount;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(const KeyCode keyCode)
			: KeyEvent{ keyCode } {}

		const std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Released: " << keyCode;
			return ss.str();
		}

		EVENT_TYPE(Event::Type::KeyRelease)
	};
}
