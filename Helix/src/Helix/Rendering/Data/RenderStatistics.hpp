#pragma once

#include "stdafx.hpp"

struct RenderStatistics
{
public:
	RenderStatistics()
		:vertices{}, triangles{}, lights{}, shadows{}, drawCalls{}, screenSize{}
	{
		t0 = std::chrono::high_resolution_clock::now();
		t1 = std::chrono::high_resolution_clock::now();
		deltaTime = t1 - t0;
	}

	void reset()
	{
		vertices = 0;
		triangles = 0;
		lights = 0;
		shadows = 0;
		drawCalls = 0;

		t0 = std::chrono::high_resolution_clock::now();
	}
	void measure()
	{
		t1 = std::chrono::high_resolution_clock::now();
		deltaTime = t1 - t0;
	}

	unsigned int vertices;
	unsigned int triangles;
	unsigned int lights;
	unsigned int shadows;
	unsigned int drawCalls;

	glm::vec2 screenSize;

	DeltaTime deltaTime;

private:
	std::chrono::high_resolution_clock::time_point t0;
	std::chrono::high_resolution_clock::time_point t1;
};
