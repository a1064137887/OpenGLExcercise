#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	this->position = position;
	this->worldUp = worldUp;
	forward = glm::normalize(target - position);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp)
{
	this->position = position;
	this->worldUp = worldUp;
	this->pitch = pitch;
	this->yaw = yaw;
	forward.x = glm::cos(pitch) * glm::sin(yaw);
	forward.y = glm::sin(pitch);
	forward.z = glm::cos(pitch) * glm::cos(yaw);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}

Camera::~Camera()
{

}


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, worldUp);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	pitch += deltaY * 0.001f;
	yaw += deltaX * 0.001f;

	UpdateCameraVector();
}

void Camera::UpdateCameraPosition()
{
	position += forward * forwardSpeed * 0.01f + right * rightSpeed * 0.01f + up * upSpeed * 0.01f;
}

void Camera::UpdateCameraVector()
{
	forward.x = glm::cos(pitch) * glm::sin(yaw);
	forward.y = glm::sin(pitch);
	forward.z = glm::cos(pitch) * glm::cos(yaw);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(forward, right));
}