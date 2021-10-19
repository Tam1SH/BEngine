#pragma once
#include "BaseRenderWindow.h"
#include <vector>
#include "RenderBuffer.hpp"
#include "Vertex.h"
#include "Camera.hpp"
namespace BEbraEngine {
	class AbstractRender {
	public:
		virtual void Create(BaseWindow* window) = 0;
		virtual RenderBuffer* CreateIndexBuffer(std::vector<uint32_t> indices) = 0;
		virtual RenderBuffer* CreateVertexBuffer(std::vector<Vertex> vertices) = 0;
		virtual RenderBuffer* CreateUniformBuffer(size_t size) = 0;
		virtual void InitCamera(Camera* alloced_camera) = 0;
	};
}