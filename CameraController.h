#pragma once
#include <glm/glm.hpp>

class CameraController
{
public:
	CameraController() = default;
	~CameraController() = default;

	bool OnKeyPressed(int key, int action);
	bool OnMouseMoved(float mouseX, float mouseY);
	

	void UpdateCamera(float deltaTime, struct CameraUniform& cameraUniform);
	

private:

	glm::vec2 inputAxis{0.f,0.f};
	float amount_up;
	float amount_down;
	float rotate_horizontal =0.f;
	float old_rotate_horizontal =0.f;
	float rotate_vertical =0.f;
	float scroll;
	float speed = 1.f;
	float sensitivity = 10.f;
};
