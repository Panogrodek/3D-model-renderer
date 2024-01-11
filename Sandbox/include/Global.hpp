#pragma once
#include <GLM/glm.hpp>

namespace window {
	static glm::uvec2 size{ 1920,1080 };
	static glm::vec4 clear_color{ 0.2f, 0.3f, 0.3f, 1.0f };
}

inline float dt{};
inline float fdt{};

inline glm::vec3 lightDirection{ 0.f,1.5f,0.f };