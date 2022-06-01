#pragma once

#include "stdafx.hpp"

#include "Helix/Event/Base/Event.hpp"

namespace hlx
{
	class Layer
	{
	public:
		Layer(const std::string& name)
			:m_name{ name }, enabled{ true } {}
		virtual ~Layer() {}

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {} //TODO: deltaTime
		virtual void onEvent(Event& m_event) {}

		const std::string& getName()
		{
			return m_name;
		}
		void setName(const std::string& name)
		{
			m_name = name;
		}

		bool enabled;

	protected:
		std::string m_name;
	};
}
