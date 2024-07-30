#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, glm::vec3 target);

	enum Movement {
		MOVE_FORWARD,
		MOVE_BACKWARD,
		MOVE_UPWARD,
		MOVE_DOWNWARD,
		MOVE_LEFT,
		MOVE_RIGHT,

		LOOK_UP,
		LOOK_DOWN,
		LOOK_LEFT,
		LOOK_RIGHT
	};

	void move(Movement m);

	glm::mat4 getLookAt();
	void setPosition(const glm::vec3& position);
	glm::vec3 getPosition();
	void setTarget(const glm::vec3& target);
	glm::vec3 getTarget();
	glm::vec3 getCameraDirection();

	float deltaTime;

private:
	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	glm::mat4 m_lookAt;

	float m_translate_speed;
	float m_lookaround_angle_mag_degrees;

	void setDefaults(glm::vec3 position = glm::vec3(0.0,0.0,1.0), glm::vec3 target = glm::vec3(0.0,0.0,-1.0));
	void updateVectors();
};
