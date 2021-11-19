#pragma once
#include "IRenderObjectFactory.hpp"
#include "RenderBufferPool.hpp"
#include "MeshFactory.hpp"
#include "DXTextureFactory.hpp"

namespace BEbraEngine {
	class DXRender;
}
namespace BEbraEngine {

	class DXRenderObjectFactory : public IRenderObjectFactory
	{
	public:
		void BindTransform(std::shared_ptr<PointLight> light, std::shared_ptr<Transform> transform) override;
		void BindTransform(std::shared_ptr<RenderObject> object, std::shared_ptr<Transform> transform) override;
		RenderObject* createObject() override;
		PointLight* createLight(const Vector3& color, const Vector3& position) override;
		DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) override;
		void setContext(AbstractRender* render) override;
		void destroyObject(std::shared_ptr<RenderObject> object) override;
		void destroyPointLight(std::shared_ptr<PointLight> light) override;
		void setModel(RenderObject* object, std::string& path) override;

	private:
		std::unique_ptr<RenderBufferPool> _poolofObjects;
		std::unique_ptr<RenderBufferPool> _poolofPointLights;
		std::unique_ptr<RenderBufferPool> _poolofDirLights;

		std::shared_ptr<RenderBufferView> storage;

		VkDescriptorSet set;

		DXRender* render;
		DXTextureFactory* textureFactory;
		std::unique_ptr<MeshFactory> meshFactory;
	};
}

