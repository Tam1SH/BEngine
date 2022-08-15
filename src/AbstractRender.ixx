
#include "platform.hpp"

export module Render;
import <span>;
import <vector>;
import <memory>;
import RenderData;
import Vertex;
import Camera;
import RenderObjects;
import RenderBuffer;
import Vector3;
import BaseRenderWindow;

using std::vector;
using std::shared_ptr;

namespace BEbraEngine {
	class SimpleCamera;
	export class RenderObjectFactory;
	class RenderObject;
	class Light;
	class DirectionLight;
	export class RenderWorld;
}




namespace BEbraEngine {

	export struct BitMap {
	public:
		struct Rows {
			struct pixel {
				char x, y, z;
			};
			unsigned int* rows;
			pixel operator[](size_t index) const {
				auto pixel_ = rows + index;
				auto comp_ = pixel{
					*((char*)pixel_ + 2),
					*((char*)pixel_ + 1),
					*((char*)pixel_)
				};
				return comp_;
			}
		};
		Rows& operator[](int index)
		{
			return at(index);
		}

		virtual Rows& at(int index) = 0;
		virtual ~BitMap() {}
	};

	export class RenderAllocator {
	public:
		enum class TypeBuffer {
			Storage,
			Uniform,
			StorageDynamic, //only vulkan
			UniformDynamic //only vulkan
		};

		virtual RenderBuffer* createIndexBuffer(std::span<uint32_t> indices) = 0;
		virtual RenderBuffer* createVertexBuffer(std::span<Vertex> vertices) = 0;
		virtual RenderBuffer* createUniformBuffer(uint32_t size) = 0;
		virtual RenderBuffer* createStorageBuffer(uint32_t size) = 0;
		virtual uint32_t alignmentBuffer(uint32_t originalSize, RenderAllocator::TypeBuffer type) = 0;
		virtual void destroyBuffer(RenderBuffer* buffer) = 0;
	};

	export class Render {
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
		virtual void addGlobalLight(DirectionLight& globalLight) = 0;
		virtual void addCamera(SimpleCamera& camera) = 0; 
		virtual void removeCamera(SimpleCamera& camera) = 0;

		virtual RenderObjectFactory* getRenderObjectFactory() = 0;
		virtual void update() = 0;
		virtual void prepareDraw() = 0;
		virtual void drawFrame() = 0;
		virtual void drawLine(const Vector3& from, 
							  const Vector3& to, 
							  const Vector3& color) = 0;

		virtual Type getType() = 0;
		virtual void setWorld(RenderWorld& world) { this->world = &world; }
		virtual uint32_t alignmentBuffer(uint32_t originalSize, Render::TypeBuffer type) = 0;
		virtual ~Render() {}
	protected:
		RenderWorld* world;
	};


}