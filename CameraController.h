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
	float mouseRotateHorizontal = 0.f;
	float mouseRotateVertical = 0.f;
	float scroll;
	float dirSpeed = 1.f;
	float rotSpeed = 200.f;
	float sensitivity = 15.f;

	std::bitset<6> DirInputs;
	std::bitset<4> RotInputs;
	std::bitset<4> LightInputs;
	bool mouseButtonDown = false;
};
