#include "Camera.h"
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera()
{
	Position = vec3(0.f);
	Yaw = 0.f;
	Pitch = 0.f;
}

Camera::Camera(vec3 position, f32 yaw, f32 pitch) :
	Position(position), Yaw(yaw), Pitch(pitch)
{
}

mat4 Camera::CalcViewMatrix()
{
	return glm::lookAtRH(Position, Position + GetCamForward(), WorldUp);
}

vec3 Camera::GetCamForward()
{
	glm::vec3 dir;
	dir.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	dir.y = -sin(glm::radians(Pitch));
	dir.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
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
