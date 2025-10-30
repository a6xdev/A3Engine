#pragma once
#include <chrono>
#include <string>
#include <unordered_map>
#include <iostream>

namespace Profile {
	enum class BenchmarkType {
		INIT,
		PROCESS,
		SHUTDOWN
	};

	class Benchmark {
	public:
		Benchmark(std::string name, BenchmarkType type) {
			m_startTimePoint = std::chrono::high_resolution_clock::now();
			m_name = name;
			m_type = type;
		};
		~Benchmark() { stop(); };

		void stop();
	private:
		std::string m_name = "";
		BenchmarkType m_type;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
	};

	std::unordered_map<std::string, double> getProcessResult();

	void printInitResult();
	void printShutdownResult();
}
