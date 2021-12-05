#pragma once
#include <vector>

namespace BEbraEngine {
	class Vertex;
	class Camera;
	class BaseWindow;
	class IRenderObjectFactory;
	class RenderObject;
	class PointLight;
	class DirectionLight;
	class RenderBuffer;
}

namespace std {
	template<typename T, typename D>
	class unique_ptr;
	template<class T>
	class shared_ptr;
	template <class T, class Alloc>
	class vector;
}

namespace BEbraEngine {

	class RenderData {
		std::vector<std::shared_ptr<RenderObject>> objects;
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
			Vulkan,
			DirectX, //11
			OpenGL, //4.2
			OpenGL_ES = OpenGL //3.2
		};
	public:
		virtual void create(BaseWindow* window) = 0;
		virtual RenderBuffer* createIndexBuffer(std::vector<uint32_t> indices) = 0;
		virtual RenderBuffer* createVertexBuffer(std::vector<Vertex> vertices) = 0;
		virtual RenderBuffer* createUniformBuffer(size_t size) = 0;
		virtual RenderBuffer* createStorageBuffer(size_t size) = 0;
		virtual void destroyBuffer(RenderBuffer* buffer) = 0;
		
		virtual void selectMainCamera(Camera* camera) = 0;
		virtual void addObject(std::shared_ptr<RenderObject> object) = 0;
		virtual void addLight(std::shared_ptr<PointLight> light) = 0;
		virtual void removeObject(std::shared_ptr<RenderObject> object) = 0;
		virtual void removeLight(std::shared_ptr<PointLight> light) = 0;
		virtual void addGlobalLight(std::shared_ptr<DirectionLight> globalLight) = 0;
		virtual void addCamera(std::shared_ptr<Camera> camera) = 0; 
		virtual void removeCamera(std::shared_ptr<Camera> camera) = 0;

		virtual IRenderObjectFactory* getRenderObjectFactory() = 0;
		virtual void drawFrame() = 0;
		virtual Type getType() = 0;
		virtual size_t alignmentBuffer(size_t originalSize, AbstractRender::TypeBuffer type) = 0;
		virtual ~AbstractRender() {}
	};
}