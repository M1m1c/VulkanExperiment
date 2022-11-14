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

	}

	return retval;
}

bool CameraController::OnMouseMoved(float mouseX, float mouseY)
{
	rotate_horizontal = mouseX;
	rotate_vertical = mouseY;
	///*else
	//{
	//	rotate_horizontal = 0.f;
	//	rotate_vertical = 0.f;
	//}*/

	return false;
}

bool CameraController::OnMouseButtonInput(int key, int action)
{
	int value = action == GLFW_PRESS || action == GLFW_REPEAT ? 1 : 0;

	mouseButtonDown = value;

	if (value == 0)
	{
		rotate_horizontal = 0.f;
		rotate_vertical = 0.f;
	}

	return value;
}

void CameraController::UpdateCamera(float deltaTime, CameraUniform& cameraUniform)
{
	//Directionals

	auto& cam = cameraUniform.Cam;
	auto forward = cam.GetCamForward();

	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.f, 0.f, 1.f)));

	inputAxis.x = (DirInputs[0] == 1 ? 1.f : (DirInputs[1] == 1 ? -1.f : 0.f));
	inputAxis.y = (DirInputs[2] == 1 ? -1.f : (DirInputs[3] == 1 ? 1.f : 0.f));
	inputAxis.z = (DirInputs[4] == 1 ? 1.f : (DirInputs[5] == 1 ? -1.f : 0.f));

	glm::vec3 dir = glm::normalize((forward * inputAxis.x) + (right * inputAxis.y) + (WorldUp * inputAxis.z));

	dir = glm::isnan(dir).b ? glm::vec3(0.f) : dir;
	cam.Position = cam.Position + (dir * speed * deltaTime);


	//Rotation

	if (mouseButtonDown)
	{
		auto widthHeight = cameraUniform.Proj.GetWidthHeight();

		auto halfWidth = (widthHeight.x * 0.5f);
		auto halfHeight = (widthHeight.y * 0.5f);

		auto yawDir = glm::clamp(rotate_horizontal - halfWidth, -halfWidth, halfWidth);
		auto pitchDir = glm::clamp(rotate_vertical - halfHeight, -halfHeight, halfHeight);
		//auto yawDir = rotate_horizontal < (widthHeight.x * 0.5) ? -1.f : rotate_horizontal >(widthHeight.x * 0.5) ? 1.f : 0.f;

		cam.Yaw += glm::radians(yawDir) * sensitivity * deltaTime;
		cam.Pitch -= glm::radians(pitchDir) * sensitivity * deltaTime;
	}
	
}
