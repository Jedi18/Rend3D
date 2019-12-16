#include "Camera.h"

Camera::Camera(float fov)
	:
	view(1.0f),
	FOV(fov)
{
}

glm::mat4 & Camera::GetView()
{
	return view;
}

void Camera::MoveCamera(MoveDirection dir, float& deltaTime)
{
	float moveSpeed =  -deltaTime; // negative because we want camera to move in opposite direction

	if (dir == Camera::MoveDirection::UP)
	{
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -moveSpeed));
	}

	if (dir == Camera::MoveDirection::DOWN)
	{
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, moveSpeed));
	}

	if (dir == Camera::MoveDirection::LEFT)
	{
		view = glm::translate(view, glm::vec3(-moveSpeed, 0.0f, 0.0f));
	}

	if (dir == Camera::MoveDirection::RIGHT)
	{
		view = glm::translate(view, glm::vec3(moveSpeed, 0.0f, 0.0f));
	}
}
