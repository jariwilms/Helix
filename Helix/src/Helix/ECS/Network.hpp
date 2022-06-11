#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/System/System.hpp"

namespace hlx
{
	class Network
	{
		template<typename System>
		std::shared_ptr<System> registerSystem()
		{
			auto& info = typeid(System);
			auto hash = info.hash_code();

			HLX_CORE_ASSERT(m_systems.find(hash) != m_systems.end(), "System has already been registered");

			return m_systems.insert(std::make_pair(hash, std::make_shared<System>()));
		}

		std::unordered_map<size_t, std::shared_ptr<System>>& getSystems()
		{
			return m_systems;
		}

	private:
		std::unordered_map<size_t, std::shared_ptr<System>> m_systems;
	};
}
