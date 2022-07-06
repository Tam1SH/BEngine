#include "platform.hpp"
#include <boost/filesystem.hpp>

export module IRenderObjectFactory;
import RenderObjects;
import Camera;
import ITextureFactory;
import Transform;
import AbstractRender;
import Vector3;
import <memory>;
import <optional>;
import <string>;

using std::shared_ptr;
using std::unique_ptr;
using std::optional;

namespace BEbraEngine {
	class ITextureFactory;
	class IVisitorGameComponentDestroyer;
	export class RenderWorld;
}

namespace BEbraEngine {
	

	export class IRenderObjectFactory {
	public:
		virtual ~IRenderObjectFactory() {}

		virtual optional<RenderObject*> create(const RenderObjectCreateInfo& info) = 0;

		virtual ITextureFactory& getTextureFactory() = 0;

		virtual void setWorld(RenderWorld& world) = 0;

		virtual void setComponentDestroyer(IVisitorGameComponentDestroyer& destroyer) = 0;

		virtual optional<Material*> createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info) = 0;

		virtual void setMaterial(RenderObject& obj, Material& material) = 0;

		virtual void bindTransform(Light& light, Transform& transform) = 0;

		virtual void bindTransform(RenderObject& object, Transform& transform) = 0;

		virtual Light* createLight(const Vector3& color, const Vector3& position) = 0;

		virtual SimpleCamera* createCamera(const Vector3& position) = 0;

		virtual DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) = 0;

		virtual void setContext(AbstractRender* render) = 0;

		virtual void destroyObject(RenderObject& object) = 0;

		virtual void destroyPointLight(Light& light) = 0;

		virtual void destroyCamera(SimpleCamera& camera) = 0;

		virtual void setModel(RenderObject& object, const std::string& path) = 0;

	};
}