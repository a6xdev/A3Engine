#include "Timer.h"

#include "../core/Engine.h"

void Timer::start(float duration) {
	m_duration = duration;
	m_time = 0.0f;
	m_running = true;
	m_finished = false;
}

void Timer::update() {
	if (!m_running) { return; };
	m_time += Engine::getDeltaTime();
	if (m_time >= m_duration) {
		m_running = false;
		m_finished = true;
	}
}

void Timer::reset() {
	m_time = 0.0f;
	m_duration = 0.0f;
	m_running = false;
}