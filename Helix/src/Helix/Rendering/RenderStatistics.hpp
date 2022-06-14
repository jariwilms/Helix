#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

struct RenderStatistics
{
public:
	RenderStatistics()
		:vertices{}, triangles{}, lights{}, shadows{}, screenSize{}, drawCalls{} {}

	void reset()
	{
		vertices = 0;
		triangles = 0;

		lights = 0;
		shadows = 0;

		drawCalls = 0;

		t0 = std::chrono::high_resolution_clock::now();
	}

	void tick()
	{
		t1 = std::chrono::high_resolution_clock::now();
	}

	unsigned int vertices;
	unsigned int triangles;

	unsigned int lights;
	unsigned int shadows;

	glm::vec2 screenSize;

	unsigned int drawCalls;

	std::chrono::high_resolution_clock::time_point t0;
	std::chrono::high_resolution_clock::time_point t1;
};
