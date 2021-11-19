#include "RenderObject.hpp"
namespace BEbraEngine {
	class DXRenderObject : public RenderObject {
		void release() override {}
	};
	class DXPointLight : public PointLight { };
	class DXDirLight : public DirectionLight { };
}