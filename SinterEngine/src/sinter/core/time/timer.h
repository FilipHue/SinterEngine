#pragma once

// Internal
#include <sinter/core/typedefs.h>

// STL
#include <chrono>

namespace sinter::core
{

	class Timer
	{
	public:
		Timer(b8 p_startImmediately = false);
		virtual ~Timer() = default;

		void Start();
		void Pause();
		void Stop();
		void Resume();
		void Reset();
		void Restart();

		f64 GetElapsedSeconds() const;
		f64 GetElapsedMilliseconds() const;

		b8 IsRunning() const;
		b8 IsPaused() const;

	private:
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		TimePoint m_startTime;
		f64 m_elapsedTime;
		b8 m_running;
		b8 m_paused;
	};

}