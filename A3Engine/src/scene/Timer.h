#pragma once

class Timer {
public:
	Timer() {};

	// Duration in seconds
	void start(float duration);
	void update();
	void reset();
	
	bool finished() const { return m_finished; }
private:
	float m_duration = 0.0f;
	float m_time = 0.0f;
	bool m_running = false;
	bool m_finished = false;
};