#include "Camera.h"

Camera::Camera(float fov)
	:
	cameraPos(0.0f, 0.0f, 0.0f),
	cameraFront(0.0f, 0.0f, -1.0f),
	cameraUp(0.0f, 1.0f, 0.0f),
	FOV(fov),
	firstused(false)
{
}

glm::mat4 Camera::GetView()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::MoveCamera(MoveDirection dir, float& deltaTime)
{
	float moveSpeed =  deltaTime; // negative because we want camera to move in opposite direction

	if (dir == Camera::MoveDirection::UP)
	{
		cameraPos += moveSpeed * cameraFront;
	}

	if (dir == Camera::MoveDirection::DOWN)
	{
		cameraPos -= moveSpeed * cameraFront;
	}

	if (dir == Camera::MoveDirection::LEFT)
	{
		glm::vec3 perpend = glm::normalize(glm::cross(cameraFront, cameraUp));
		cameraPos -= moveSpeed * perpend;
	}

	if (dir == Camera::MoveDirection::RIGHT)
	{
		glm::vec3 perpend = glm::normalize(glm::cross(cameraFront, cameraUp));
		cameraPos += moveSpeed * perpend;
	}
}

void Camera::RotateCamera(double & xpos, double & ypos)
{
	if (!firstused)
	{
		mousex = xpos;
		mousey = ypos;
		firstused = true;
	}
	
	double diffx = xpos - mousex;
	double diffy = ypos - mousey;

	float sensitivity = 0.5f;

	yaw += diffx * sensitivity;
	pitch -= diffy * sensitivity;

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);

	mousex = xpos;
	mousey = ypos;
}
