#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::mat4 Mat4;

struct Transform2D {
	Vector2 Size;
	Vector2 Position;
	float Rotation;

	Transform2D() : Size(0.0f), Position(0.0f), Rotation(0.0f) {}

	Mat4 GetModelMatrix() {
		Mat4 model_matrix = Mat4(1.0f);
		model_matrix = glm::translate(model_matrix, Vector3(Position, 0.0f));
		model_matrix = glm::rotate(model_matrix, glm::radians(Rotation), Vector3(0.0f, 0.0f, 1.0f));
		model_matrix = glm::scale(model_matrix, glm::vec3(Size, 0.0f));

		return model_matrix;
	}
};

struct Transform3D {
	Vector3 Size;
	Vector3 Position;
	Vector3 Rotation;

	Transform3D() : Size(0.0f), Position(0.0f), Rotation(0.0f) {}

	Mat4 GetModelMatrix() {
		Mat4 model_matrix = Mat4(1.0f);
		model_matrix = glm::translate(model_matrix, Vector3(Position));

		model_matrix = glm::rotate(model_matrix, glm::radians(Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
		model_matrix = glm::rotate(model_matrix, glm::radians(Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
		model_matrix = glm::rotate(model_matrix, glm::radians(Rotation.z), Vector3(0.0f, 0.0f, 1.0f));

		model_matrix = glm::scale(model_matrix, Vector3(Size));

		return model_matrix;
	}
};