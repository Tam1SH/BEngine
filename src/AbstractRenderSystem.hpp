#pragma once
#include <vector>
#include "RenderObject.hpp"
//TODO: хуй знает, использовать это как интерфейс для классов либо как полноценный класс, только скрывая реализацию граф. апи
namespace BEbraEngine {
	class Vertex;
	class Camera;
	class BaseWindow;
	class IRenderObjectFactory;
	class RenderObject;
}
namespace BEbraEngine {

	
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
			DirectX,
			OpenGL_ES
		};
	public:
		virtual void Create(BaseWindow* window) = 0;
		virtual RenderBuffer* createIndexBuffer(std::vector<uint32_t> indices) = 0;
		virtual RenderBuffer* createVertexBuffer(std::vector<Vertex> vertices) = 0;
		virtual RenderBuffer* createUniformBuffer(size_t size) = 0;
		virtual RenderBuffer* createStorageBuffer(size_t size) = 0;
		virtual void DestroyBuffer(RenderBuffer* buffer) = 0;
		
		//TODO: сомнительная хуйня
		virtual void InitCamera(Camera* alloced_camera) = 0;
		virtual void addObject(std::weak_ptr<RenderObject> object) = 0;
		virtual void addLight(std::weak_ptr<PointLight> light) = 0;
		virtual void addGlobalLight(std::weak_ptr<DirLight> globalLight) = 0;

		virtual IRenderObjectFactory* getRenderObjectFactory() = 0;
		virtual Type getType() = 0;
		virtual ~AbstractRender() {}
	};
}