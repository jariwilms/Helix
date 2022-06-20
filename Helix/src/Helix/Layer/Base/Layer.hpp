#pragma once

#include "stdafx.hpp"

#include "Helix/Event/Base/Event.hpp"

namespace hlx
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			:m_name{ name }, m_enabled{ true } {}
		virtual ~Layer() = default;

		virtual void update(DeltaTime deltaTime) {}
		virtual void render() {}
		virtual void renderUI() {}

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onEvent(Event& event) {}

		bool isEnabled() { return m_enabled; }
		void setEnabled(bool state) { m_enabled = state; }

		const std::string& getName() { return m_name; }
		void setName(const std::string& name) { m_name = name; }

	protected:
		bool m_enabled; //TODO: -> private?
		std::string m_name;
	};
}
