#pragma once

#include "stdafx.hpp"

#include "Helix/Event/Layer.hpp"

namespace hlx
{
	class LayerStack
	{
	public:
		LayerStack()
			: m_layers{}, m_layerInsertIndex {} {}
		~LayerStack()
		{
			for (auto* layer : m_layers)
				delete layer;
		}

		void pushLayer(Layer* layer)
		{
			m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
			++m_layerInsertIndex;
		}
		void popLayer(Layer* layer)
		{
			auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer);

			if (it != m_layers.begin() + m_layerInsertIndex)
			{
				layer->onDetach();
				m_layers.erase(it);
				--m_layerInsertIndex;
			}
		}

		void pushOverlay(Layer* overlay)
		{
			m_layers.emplace_back(overlay);
		}
		void popOverlay(Layer* overlay)
		{
			auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), overlay);

			if (it != m_layers.end())
			{
				overlay->onDetach();
				m_layers.erase(it);
			}
		}

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_layers.rend(); }

	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layerInsertIndex;
	};
}
