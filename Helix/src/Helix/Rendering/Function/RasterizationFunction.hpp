#pragma once

#include "stdafx.hpp"

enum RasterizationFunction
{
	Point		= BIT(0), 
	Line		= BIT(1), 
	Fill		= BIT(2)
};
