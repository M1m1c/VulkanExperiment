#pragma once
#include <glm/glm.hpp>

using namespace glm;

static const  glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

struct Camera
{
public:
	Camera();
	Camera(vec3 position, f32 yaw, f32 pitch);
	mat4 CalcViewMatrix();
	vec3 GetCamForward();
	vec3 Position;
	f32 Pitch;
	f32 Yaw;
};

struct Projection {
public:
	Projection();
	Projection(u32 width, u32 height, f32 fov, f32 znear, f32 zfar);
	void Resize(u32 width, u32 height);
	mat4 CalcProjectionMatrix();
	vec2 GetWidthHeight();
	f32 Aspect;
	f32 Fov;
	f32 Z_near;
	f32 Z_far;
private:
	u32 Width;
	u32 Height;
};

struct CameraUniform
{
public:
	CameraUniform();
	CameraUniform(Camera cam, Projection proj);
	mat4 CalcMVP();
	Camera Cam;
	Projection Proj;
};