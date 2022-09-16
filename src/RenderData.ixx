export module RenderData;
import <vector>;
import <span>;

export namespace BEbraEngine {
	class RenderObject;
	class SimpleCamera;
	class DirectionLight;
	class Light;
}

namespace BEbraEngine {

	export class RenderData {
	public:
		std::vector<RenderObject*> objects;
		SimpleCamera* mainCamera;
		std::span<DirectionLight*> globalLights;
		std::vector<Light*> lights;
	};
}
