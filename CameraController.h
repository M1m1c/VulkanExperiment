#pragma once
#include <glm/glm.hpp>

class CameraController
{
public:
	CameraController() = default;
	~CameraController() = default;

	bool OnKeyPressed(int key, int action);
	

	void UpdateCamera(float deltaTime, struct Camera& camera);
	

private:

	glm::vec2 inputAxis{0.f,0.f};
	//glm::vec2 inputYAxis{0.f,0.f};
	float amount_left;
	float amount_right;
	float amount_forward;
	float amount_backward;
	float amount_up;
	float amount_down;
	float rotate_horizontal;
	float rotate_vertical;
	float scroll;
	float speed = 1.f;
	float sensitivity = 0.4f;
};
