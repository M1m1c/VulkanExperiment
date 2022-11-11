#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>

class CameraController
{
public:
	CameraController() = default;
	~CameraController() = default;

	inline bool OnKeyPressed(int key, int action)
	{
		bool retval = false;
		float amount = action == GLFW_PRESS ? 1.0f : 0.0f;
		switch (key)
		{
		case GLFW_KEY_W:
		case GLFW_KEY_UP:
			amount_forward = amount;
			retval = true;
			break;


		}

		return retval;
	}

	inline void UpdateCamera(float deltaTime, Camera& camera)
	{

	}

private:
	float amount_left;
	float amount_right;
	float amount_forward;
	float amount_backward;
	float amount_up;
	float amount_down;
	float rotate_horizontal;
	float rotate_vertical;
	float scroll;
	float speed = 4.0f;
	float sensitivity = 0.4f;
};
