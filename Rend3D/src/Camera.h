#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Camera
{
private:
	glm::mat4 view;
public:
	enum class MoveDirection {UP, DOWN, LEFT, RIGHT};
	float FOV;
	Camera(float fov);
	glm::mat4& GetView();
	void MoveCamera(MoveDirection dir, float& deltaTime);
};