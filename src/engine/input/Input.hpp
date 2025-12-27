#pragma once

#include "../Core.hpp"
#include "keycodes.h"

namespace Input {
	A3_API void Init();
	A3_API void Update();

	A3_API bool KeyDown(unsigned int keycode);
	A3_API bool KeyPressed(unsigned int keycode);
	A3_API float KeyStrength(unsigned int keycode);

	A3_API bool LeftMouseDown();
	A3_API bool RightMouseDown();
}