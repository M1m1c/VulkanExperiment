#include "CameraController.h"

#include "Camera.h"
#include <GLFW/glfw3.h>

bool CameraController::OnKeyPressed(int key, int action)
{
	bool retval = false;
	float amount = action == GLFW_PRESS  || action == GLFW_REPEAT ? 1.0f : 0.0f;
	switch (key)
	{
	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		amount_forward = amount;
		retval = true;
		break;

	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		amount_backward = amount;
		retval = true;
		break;
		
	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		amount_left = amount;
		retval = true;
		break;

	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		amount_right = amount;
		retval = true;
		break;

	case GLFW_KEY_SPACE:
		amount_up = amount;
		retval = true;
		break;

	case GLFW_KEY_LEFT_SHIFT:
		amount_down = amount;
		retval = true;
		break;

	}

	return retval;
}

void CameraController::UpdateCamera(float deltaTime, Camera& camera)
{
	//Directional input
	float yaw_sin = sin(camera.Yaw);
	float yaw_cos = cos(camera.Yaw);

	
	auto forward = camera.GetCamForward();
	//-cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
	//glm::vec3 forward = glm::normalize(glm::vec3(yaw_cos, 0.0f, yaw_sin));
	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.f, 0.f, 1.f)));


	auto xDir = amount_forward - amount_backward;
	auto yDir = amount_right - amount_left;
	glm::vec3 dir = glm::normalize((forward * xDir) + (right * yDir));


	dir = glm::isnan(dir).b ? glm::vec3(0.f) : dir;
	camera.Position = camera.Position +( dir * speed * deltaTime);
	/*camera.Position += forward * (amount_forward - amount_backward) * speed * deltaTime;
	camera.Position += right * (amount_right - amount_left) * speed * deltaTime;*/


}
