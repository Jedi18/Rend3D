#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Camera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	double mousex, mousey;
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool firstused; // boolean to enable functionality after first movement of mouse (to avoid jump during starting)
	bool FLY_MODE;
public:
	enum class MoveDirection {UP, DOWN, LEFT, RIGHT};
	float FOV;
	Camera(float fov, bool fly_mode = true);
	glm::mat4 GetView();
	void MoveCamera(MoveDirection dir, float& deltaTime);
	void RotateCamera(double& xpos, double& ypos);
};