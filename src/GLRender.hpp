#pragma once
#include "AbstractRender.hpp"
namespace BEbraEngine {
	class GLWindow;
}
namespace BEbraEngine {

	class GLRender : public AbstractRender
	{
	public:
		void create(BaseWindow* window) override;
		RenderBuffer* createIndexBuffer(std::vector<uint32_t> indices) override;
		RenderBuffer* createVertexBuffer(std::vector<Vertex> vertices) override;
		RenderBuffer* createUniformBuffer(uint32_t size) override;
		RenderBuffer* createStorageBuffer(uint32_t size) override;
		void destroyBuffer(RenderBuffer* buffer) override;
		void selectMainCamera(SimpleCamera* camera) override;
		void addObject(std::shared_ptr<RenderObject> object) override;
		void addLight(std::shared_ptr<PointLight> light) override;
		void removeObject(std::shared_ptr<RenderObject> object) override;
		void removeLight(std::shared_ptr<PointLight> light) override;
		void addGlobalLight(std::shared_ptr<DirectionLight> globalLight) override;
		void addCamera(std::shared_ptr<SimpleCamera> camera) override;
		void removeCamera(std::shared_ptr<SimpleCamera> camera) override;

		IRenderObjectFactory* getRenderObjectFactory() override;
		void drawFrame() override;
		Type getType() override;
		uint32_t alignmentBuffer(uint32_t originalSize, AbstractRender::TypeBuffer type) override;

	private:
		GLWindow* window;


	};

}

