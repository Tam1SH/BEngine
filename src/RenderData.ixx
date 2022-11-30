#include <vector>
#include <span>
export module RenderData;

export namespace BEbraEngine {
	struct RenderObject;
	struct SimpleCamera;
	struct DirectionLight;
	struct Light;
}

namespace BEbraEngine {

	export struct RenderData {
		std::vector<RenderObject*> objects;
		SimpleCamera* mainCamera;
		std::span<DirectionLight*> globalLights;
		std::vector<Light*> lights;
	};
}
