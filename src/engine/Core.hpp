#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>

#ifdef _WIN32
	#ifdef A3_EXPORT
		#define A3_API __declspec(dllexport)
	#else
		#define A3_API __declspec(dllimport)
	#endif
#else
	#define A3_API
#endif

namespace Core {
	A3_API void Init();
}