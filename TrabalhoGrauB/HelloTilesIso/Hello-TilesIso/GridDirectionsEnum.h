#pragma once
#include <GLFW/glfw3.h>

enum GridDirectionsEnum {
	NORTH = GLFW_KEY_KP_8,
	SOUTH = GLFW_KEY_KP_2,
	EAST = GLFW_KEY_KP_6,
	WEST = GLFW_KEY_KP_4,
	CENTER = GLFW_KEY_KP_5,
	NORTH_EAST = GLFW_KEY_KP_9,
	NORTH_WEST = GLFW_KEY_KP_7,
	SOUTH_EAST = GLFW_KEY_KP_3,
	SOUTH_WEST = GLFW_KEY_KP_1,
	ATTACK = GLFW_KEY_Q,
	WATER = GLFW_KEY_E
};
