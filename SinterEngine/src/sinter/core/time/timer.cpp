#include "sepch.h"
#include "timer.h"

// Internal
#include <sinter/core/defines.h>

namespace sinter::core
{

	Timer::Timer(b8 p_startImmediately) : m_startTime(Clock::now()), m_elapsedTime(0.0), m_running(p_startImmediately), m_paused(false)
	{
		NO_OP;
	}

	void Timer::Start()
	{
		if (!m_running)
		{
			m_startTime = Clock::now();
			m_running = true;
			m_paused = false;
		}
	}

	void Timer::Pause()
	{
		if (m_running)
		{
			auto end_time = Clock::now();
			m_elapsedTime = std::chrono::duration<f64>(end_time - m_startTime).count();
			m_running = false;
			m_paused = true;
		}
	}

	void Timer::Stop()
	{
		if (m_running)
		{
			auto end_time = Clock::now();
			m_elapsedTime = std::chrono::duration<f64>(end_time - m_startTime).count();
			m_running = false;
			m_paused = false;
		}
		else if (m_paused)
		{
			m_running = false;
			m_paused = false;
		}
		m_elapsedTime = 0.0;
	}

	void Timer::Resume()
	{
		if (m_paused)
		{
			m_startTime = Clock::now();
			m_running = true;
			m_paused = false;
		}
	}

	void Timer::Reset()
	{
		m_startTime = Clock::now();
		m_elapsedTime = 0.0;
	}

	void Timer::Restart()
	{
		m_startTime = Clock::now();
		m_elapsedTime = 0.0;
		m_running = true;
	}

	f64 Timer::GetElapsedSeconds() const
	{
		if (m_running)
		{
			auto end_time = Clock::now();
			return std::chrono::duration<f64>(end_time - m_startTime).count();
		}
		return m_elapsedTime;
	}

	f64 Timer::GetElapsedMilliseconds() const
	{
		return GetElapsedSeconds() * 1000.0;
	}

	b8 Timer::IsRunning() const
	{
		return m_running;
	}

	b8 Timer::IsPaused() const
	{
		return m_paused;
	}

} // namespace sinter::core
