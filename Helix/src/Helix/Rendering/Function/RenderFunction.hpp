#pragma once

#include "stdafx.hpp"

enum RenderFunction
{
	DepthTest		= BIT(0), 
	StencilTest		= BIT(1), 
	ScissorTest		= BIT(2), 
};