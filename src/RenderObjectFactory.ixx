#include "platform.hpp"
#include <boost/filesystem.hpp>

export module RenderObjectFactory;
import RenderObjects;
import Camera;
import TextureFactory;
import Transform;
import Render;
import Vector3;
import <memory>;
import <optional>;
import <string>;

using std::shared_ptr;
using std::unique_ptr;
using std::optional;

namespace BEbraEngine {
	class TextureFactory;
	class VisitorGameComponentDestroyer;
	export class RenderWorld;
}

namespace BEbraEngine {
	

	export class RenderObjectFactory {
	public:
		virtual ~RenderObjectFactory() {}

		virtual optional<RenderObject*> create(const RenderObjectCreateInfo& info) = 0;

		virtual TextureFactory& getTextureFactory() = 0;

		virtual void setWorld(RenderWorld& world) = 0;

		virtual void setComponentDestroyer(VisitorGameComponentDestroyer& destroyer) = 0;

		virtual optional<Material*> createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info) = 0;

		virtual void setMaterial(RenderObject& obj, Material& material) = 0;

		virtual void bindTransform(Light& light, Transform& transform) = 0;

		virtual void bindTransform(RenderObject& object, Transform& transform) = 0;

		virtual Light* createLight(const Vector3& color, const Vector3& position) = 0;

		virtual SimpleCamera* createCamera(const Vector3& position) = 0;

		virtual DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) = 0;

		virtual void setContext(Render* render) = 0;

		virtual void destroyObject(RenderObject& object) = 0;

		virtual void destroyPointLight(Light& light) = 0;

		virtual void destroyCamera(SimpleCamera& camera) = 0;

		virtual void setModel(RenderObject& object, const std::string& path) = 0;

	};
}