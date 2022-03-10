#pragma once
#include "platform.hpp"
#include "Vector3.hpp"
BE_NAMESPACE_STD_BEGIN

template<typename T, typename D>
class unique_ptr;
template<class T>
class shared_ptr;
template <class T, class Alloc>
class vector;

BE_NAMESPACE_STD_END

using BE_STD::vector;
using BE_STD::shared_ptr;

namespace BEbraEngine {
	class Vertex;
	class SimpleCamera;
	class BaseWindow;
	class IRenderObjectFactory;
	class RenderObject;
	class Light;
	class DirectionLight;
	class RenderBuffer;
}




namespace BEbraEngine {

	class RenderData {
	public:
		vector<RenderObject*> objects;
	};
	class RenderSettings {
	public:
		bool isEnable_MSAA{};

	};
	class AbstractRender {
	public:
		enum class TypeBuffer {
			Storage,
			Uniform,
			StorageDynamic, //only vulkan
			UniformDynamic //only vulkan
		};
		enum class Type {
			Vulkan
			//Metal
		};
	public:
		virtual void create(BaseWindow* window) = 0;
		virtual RenderBuffer* createIndexBuffer(vector<uint32_t> indices) = 0;
		virtual RenderBuffer* createVertexBuffer(vector<Vertex> vertices) = 0;
		virtual RenderBuffer* createUniformBuffer(uint32_t size) = 0;
		virtual RenderBuffer* createStorageBuffer(uint32_t size) = 0;
		virtual void destroyBuffer(RenderBuffer* buffer) = 0;
		virtual void updateState(RenderData& data) = 0;
		virtual void selectMainCamera(SimpleCamera& camera) = 0;
		virtual void addObject(RenderObject& object) = 0;
		virtual void addLight(Light& light) = 0;
		virtual void removeObject(RenderObject& object) = 0;
		virtual void removeLight(Light& light) = 0;
		virtual void addGlobalLight(DirectionLight& globalLight) = 0;
		virtual void addCamera(SimpleCamera& camera) = 0; 
		virtual void removeCamera(SimpleCamera& camera) = 0;

		virtual IRenderObjectFactory* getRenderObjectFactory() = 0;
		virtual void update() = 0;
		virtual void drawFrame() = 0;
		virtual void drawLine(const Vector3& from, 
							  const Vector3& to, 
							  const Vector3& color = Vector3(0)) = 0;

		virtual Type getType() = 0;
		virtual uint32_t alignmentBuffer(uint32_t originalSize, AbstractRender::TypeBuffer type) = 0;
		virtual ~AbstractRender() {}
	};
}