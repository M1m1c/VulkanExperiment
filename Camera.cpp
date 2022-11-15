#include "Camera.h"
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>


Camera::Camera()
{
	Position = vec3(0.f);
	Pitch = 0.f;
	Yaw = 0.f;
}

Camera::Camera(vec3 position, f32 pitch, f32 yaw) :
	Position(position), Pitch(pitch), Yaw(yaw)
{
}

mat4 Camera::CalcViewMatrix()
{
	glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), -Position);
	glm::mat4 rotMatrix = glm::mat4(1.0f);

	rotMatrix = glm::rotate(rotMatrix, glm::radians(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));

	return rotMatrix * transformMatrix;
}

vec3 Camera::GetCamForward()
{
	glm::vec3 dir;
	dir.x = -cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	dir.y = sin(glm::radians(Pitch));
	dir.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	return glm::normalize(dir);
}

Projection::Projection()
{
	Width = 0;
	Height = 0;
	Aspect = 0.f;
	Fov = 0.f;
	Z_near = 0.f;
	Z_far = 0.f;
}

Projection::Projection(u32 width, u32 height, f32 fov, f32 znear, f32 zfar) :
	Width(width),Height(height), Fov(fov), Z_near(znear), Z_far(zfar)
{
	Aspect = (f32)width / (f32)height;

}

void Projection::Resize(u32 width, u32 height)
{
	Aspect = (f32)width / (f32)height;
}

mat4 Projection::CalcProjectionMatrix()
{
	return glm::perspective(glm::radians(Fov), Aspect, Z_near, Z_far);
}

vec2 Projection::GetWidthHeight()
{
	return vec2(Width,Height);
}

CameraUniform::CameraUniform()
{
}

CameraUniform::CameraUniform(Camera cam, Projection proj) :
	Cam(cam), Proj(proj)
{
}

mat4 CameraUniform::CalcMVP()
{
	return Proj.CalcProjectionMatrix() * Cam.CalcViewMatrix();
}

SceneLight::SceneLight()
{
	Yaw = 0.f;
	Pitch = 0.f;
}

vec3 SceneLight::GetLightPosition()
{
	glm::mat4 rotMatrix = glm::mat4(1.0f);
	rotMatrix = glm::rotate(rotMatrix, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	return rotMatrix[0] + rotMatrix[1] + rotMatrix[2]+rotMatrix[3];
}
