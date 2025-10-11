
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Component {
	Component() = default;
};

struct Transform : Component {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 worldMatrix;
	glm::mat4 localMatrix;

	void setPosition(glm::vec3 n_position);
	void setRotation(glm::vec3 n_rotation);
	void setScale(glm::vec3 n_scale);

	glm::vec3 getPosition() { return position; };
	glm::vec3 getRotation() { return rotation; };
	glm::vec3 getScale() { return scale; };
};
