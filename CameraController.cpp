#include "CameraController.h"

#include "Camera.h"
#include <GLFW/glfw3.h>

bool CameraController::OnKeyInput(int key, int action)
{
	bool retval = false;
	int value = action == GLFW_PRESS || action == GLFW_REPEAT ? 1 : 0;
	switch (key)
	{
	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		DirInputs[0] = value;
		retval = true;
		break;

	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		DirInputs[1] = value;
		retval = true;
		break;

	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		DirInputs[2] = value;
		retval = true;
		break;

	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		DirInputs[3] = value;
		retval = true;
		break;

	case GLFW_KEY_SPACE:
		DirInputs[4] = value;
		retval = true;
		break;

	case GLFW_KEY_LEFT_SHIFT:
		DirInputs[5] = value;
		retval = true;
		break;


	case GLFW_KEY_Q:
		RotInputs[0] = value;
		retval = true;
		break;

	case GLFW_KEY_E:
		RotInputs[1] = value;
		retval = true;
		break;

	case GLFW_KEY_R:
		RotInputs[2] = value;
		retval = true;
		break;

	case GLFW_KEY_F:
		RotInputs[3] = value;
		retval = true;
		break;

	}

	return retval;
}

bool CameraController::OnMouseMoved(float mouseX, float mouseY)
{
	if (mouseButtonDown)
	{
		mouseRotateHorizontal = mouseX;
		mouseRotateVertical = mouseY;
	}

	return false;
}

bool CameraController::OnMouseButtonInput(int key, int action)
{
	int value = action == GLFW_PRESS || action == GLFW_REPEAT ? 1 : 0;

	mouseButtonDown = value;

	if (value == 0)
	{
		mouseRotateHorizontal = 0.f;
		mouseRotateVertical = 0.f;
	}

	return value;
}

void CameraController::UpdateCamera(float deltaTime, CameraUniform& cameraUniform)
{
	//Directionals

	auto& cam = cameraUniform.Cam;
	auto forward = cam.GetCamForward();

	glm::vec3 right = glm::normalize(glm::cross(forward, WorldUp));

	inputAxis.x = (DirInputs[0] == 1 ? -1.f : (DirInputs[1] == 1 ? 1.f : 0.f));
	inputAxis.y = (DirInputs[2] == 1 ? 1.f : (DirInputs[3] == 1 ? -1.f : 0.f));
	inputAxis.z = (DirInputs[4] == 1 ? 1.f : (DirInputs[5] == 1 ? -1.f : 0.f));

	glm::vec3 dir = glm::normalize((forward * inputAxis.x) + (right * inputAxis.y) + (WorldUp * inputAxis.z));

	dir = glm::isnan(dir).b ? glm::vec3(0.f) : dir;
	cam.Position = cam.Position + (dir * speed * deltaTime);


	//Rotation
	float yawDir = 0;
	float pitchDir = 0;

	if (mouseButtonDown)
	{
		auto widthHeight = cameraUniform.Proj.GetWidthHeight();

		auto halfWidth = (widthHeight.x * 0.5f);
		auto halfHeight = (widthHeight.y * 0.5f);

		yawDir = glm::clamp(mouseRotateHorizontal - halfWidth, -halfWidth, halfWidth);
		pitchDir = glm::clamp(mouseRotateVertical - halfHeight, -halfHeight, halfHeight);	
	}
	else if (RotInputs.any())
	{
		yawDir = (RotInputs[0] == 1 ? -200.f : (RotInputs[1] == 1 ? 200.f : 0.f));
		pitchDir = (RotInputs[2] == 1 ? -200.f : (RotInputs[3] == 1 ? 200.f : 0.f));
	}
	cam.Yaw += glm::radians(yawDir) * sensitivity * deltaTime;
	cam.Pitch += glm::radians(pitchDir) * sensitivity * deltaTime;
	
}
