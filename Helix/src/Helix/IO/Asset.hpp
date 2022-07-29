#pragma once

#include "Helix/IO/Format/GUID.hpp"

namespace hlx
{
	template<class T>
	class Asset
	{
	public:
		Asset() = default;
		
	private:
		GUID m_guid;
	};
}
