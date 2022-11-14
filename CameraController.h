#pragma once
#include <glm/glm.hpp>
#include <bitset>

class CameraController
{
public:
	CameraController() = default;
	~CameraController() = default;

	bool OnKeyInput(int key, int action);
	bool OnMouseMoved(float mouseX, float mouseY);
	bool OnMouseButtonInput(int key, int action);
	

	void UpdateCamera(float deltaTime, struct CameraUniform& cameraUniform);
	

private:

	glm::vec3 inputAxis{0.f,0.f,0.f};
	float amount_up;
	float amount_down;
	float rotate_horizontal =0.f;
	float old_rotate_horizontal =0.f;
	float rotate_vertical =0.f;
	float scroll;
	float speed = 1.f;
	float sensitivity = 10.f;

	std::bitset<6> DirInputs;
	//std::bitset<3> MouseInputs;
	bool mouseButtonDown = false;
};
