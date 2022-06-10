#pragma once

#include "stdafx.hpp"

struct DeltaTime
{
public:
	DeltaTime() = default;

	float toSeconds() { return m_deltaTime.count() * 0.001f; }
	float toMilliSeconds() { return m_deltaTime.count(); }

	template<typename Duration>
	Duration cast()
	{
		return std::chrono::duration_cast<Duration>(m_deltaTime);
	}

	operator float() { return m_deltaTime.count(); }
	void operator=(std::chrono::duration<long long, std::nano> duration) { m_deltaTime = duration; }

private:
	std::chrono::duration<float, std::milli> m_deltaTime;
};
