export module RenderData;
import RenderObjects;
import <vector>;
namespace BEbraEngine {
	export class RenderData {
	public:
		std::vector<RenderObject*> objects;
		std::vector<Light*> lights;
	};
}
