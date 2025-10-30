#include "Profile.h"

namespace Profile {
	std::unordered_map<std::string, double> initResult;
	std::unordered_map<std::string, double> processResult;
	std::unordered_map<std::string, double> shutdownResult;

	void Benchmark::stop() {
		static int frameCounter = 0;

		auto endTimePoint = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration<double, std::milli>(endTimePoint - m_startTimePoint).count();

		switch (m_type) {
		case BenchmarkType::INIT:
			initResult[m_name] = duration;
			break;
		case BenchmarkType::PROCESS:
			frameCounter++;

			if (frameCounter % 10 != 0)
				return;

			processResult[m_name] = duration;
			break;
		case BenchmarkType::SHUTDOWN:
			shutdownResult[m_name] = duration;
			break;
		}
	}

	std::unordered_map<std::string, double> getProcessResult() {
		return processResult;
	}

	void printInitResult() {
		std::cout << "===== Init Benchmark Results =====" << std::endl;
		for (const auto& [name, ms] : initResult) {
			std::cout << name << ": " << ms << " ms" << std::endl;
		}
		std::cout << "==================================\n";
	}

	void printShutdownResult() {
		std::cout << "===== Shutdown Benchmark Results =====" << std::endl;
		for (const auto& [name, ms] : shutdownResult) {
			std::cout << name << ": " << ms << " ms" << std::endl;
		}
		std::cout << "======================================\n";
	}
}