module;
export module RenderObjectFactory;
import Task;
import Light;
import DirectionLight;
import Camera;
import RenderObject;
import Material;
import Vector3;
import Transform;
import <optional>;
import <memory>;
using namespace std;

namespace BEbraEngine {

	export struct RenderObjectFactory {

		virtual Task<optional<Material*>> createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info) = 0;

		virtual optional<RenderObject*> create(const RenderObjectCreateInfo& info) = 0;

		virtual optional<Light*> createLight(const LightCreateInfo& info) = 0;

		virtual optional<DirectionLight*> createDirLight(const DirectionLightCreateInfo& info) = 0;

		virtual optional<SimpleCamera*> createCamera(const CameraCreateInfo& info) = 0;

		virtual void setMaterial(RenderObject& obj, Material& material) = 0;

		virtual void bindTransform(Light& light, Transform& transform) = 0;

		virtual void bindTransform(RenderObject& object, Transform& transform) = 0;

		virtual void destroyObject(RenderObject& object) = 0;

		virtual void destroyPointLight(Light& light) = 0;

		virtual void destroyCamera(SimpleCamera& camera) = 0;

		virtual void setModel(RenderObject& object, const string& path) = 0;
	};
}


