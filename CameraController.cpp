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
		inputAxis.x = amount;
		retval = true;
		break;

	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		inputAxis.x = -amount;
		retval = true;
		break;
		
	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		inputAxis.y = -amount;
		retval = true;
		break;

	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		inputAxis.y = amount;
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
	//Directionals
	auto forward = camera.GetCamForward();
	
	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.f, 0.f, 1.f)));

	glm::vec3 dir = glm::normalize((forward * inputAxis.x) + (right * inputAxis.y));

	dir = glm::isnan(dir).b ? glm::vec3(0.f) : dir;
	camera.Position = camera.Position +( dir * speed * deltaTime);



}
