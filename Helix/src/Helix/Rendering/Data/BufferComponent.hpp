#pragma once

#include "stdafx.hpp"

namespace hlx
{
	enum BufferComponent
	{
		Color = BIT(0),
		Depth = BIT(1),
		Stencil = BIT(2)
	};
}
