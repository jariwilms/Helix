#pragma once

#include "stdafx.hpp"

struct DeltaTime
{
public:
	DeltaTime() = default;

	float inSeconds() { return m_deltaTime.count() / 1000.0f; }
	float inMilliseconds() { return m_deltaTime.count(); }

	template<typename Duration>
	Duration cast() { return std::chrono::duration_cast<Duration>(m_deltaTime); }

	operator float() { return inSeconds(); }
	void operator=(std::chrono::duration<long long, std::nano> duration) { m_deltaTime = duration; }
	void operator=(float duration) { m_deltaTime = std::chrono::duration<float>(duration); }

private:
	std::chrono::duration<float, std::milli> m_deltaTime;
};
