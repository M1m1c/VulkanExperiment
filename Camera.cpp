#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(vec3 position, f32 yaw, f32 pitch) :
	Position(position), Yaw(yaw), Pitch(pitch)
{
}

mat4 Camera::CalcViewMatrix()
{
	return glm::lookAt(Position, vec3(cos(Yaw), cos(Pitch), sin(Yaw)), worldUp);
}

Projection::Projection(u32 width, u32 height, f32 fov, f32 znear, f32 zfar) :
	Fov(fov), Z_near(znear), Z_far(zfar)
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

CameraUniform::CameraUniform(Camera cam, Projection proj) :
	Cam(cam), Proj(proj)
{
}

mat4 CameraUniform::CalcMVP()
{
	return Proj.CalcProjectionMatrix() * Cam.CalcViewMatrix();
}
