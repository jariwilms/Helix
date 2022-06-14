#pragma once

#include <stdint.h>

namespace hlx
{
	class Entity
	{
	public:
		Entity(uint32_t id)
			: m_id{ id }
		{

		}

		uint32_t getId() const { return m_id; }

	private:
		uint32_t m_id;
	};
}
