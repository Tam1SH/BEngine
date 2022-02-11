#pragma once
#include "platform.hpp"

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
	class PointLight;
	class DirectionLight;
	class RenderBuffer;
}




namespace BEbraEngine {

	class RenderData {
		vector<shared_ptr<RenderObject>> objects;
	};
	class RenderSettings {
	public:
		bool isEnable_MSAA{};
		size_t countPerPixel_MSSA{};

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
		
		virtual void selectMainCamera(SimpleCamera& camera) = 0;
		virtual void addObject(RenderObject& object) = 0;
		virtual void addLight(PointLight& light) = 0;
		virtual void removeObject(RenderObject& object) = 0;
		virtual void removeLight(PointLight& light) = 0;
		virtual void addGlobalLight(DirectionLight& globalLight) = 0;
		virtual void addCamera(SimpleCamera& camera) = 0; 
		virtual void removeCamera(SimpleCamera& camera) = 0;

		virtual IRenderObjectFactory* getRenderObjectFactory() = 0;
		virtual void drawFrame() = 0;
		virtual Type getType() = 0;
		virtual uint32_t alignmentBuffer(uint32_t originalSize, AbstractRender::TypeBuffer type) = 0;
		virtual ~AbstractRender() {}
	};
}