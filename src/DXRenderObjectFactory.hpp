#pragma once
#include "IRenderObjectFactory.hpp"
#include "DXRenderBufferPool.hpp"
#include "MeshFactory.hpp"
#include "DXTextureFactory.hpp"

namespace BEbraEngine {
	class DXRender;
}
namespace BEbraEngine {

	class DXRenderObjectFactory : public IRenderObjectFactory
	{
	public:
		void bindTransform(std::shared_ptr<PointLight> light, std::shared_ptr<Transform> transform) override;
		void bindTransform(std::shared_ptr<RenderObject> object, std::shared_ptr<Transform> transform) override;
		RenderObject* createObject() override;
		PointLight* createLight(const Vector3& color, const Vector3& position) override;
		DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) override;
		Camera* createCamera(const Vector3& position) override;
		void setContext(AbstractRender* render) override;
		void destroyObject(std::shared_ptr<RenderObject> object) override;
		void destroyPointLight(std::shared_ptr<PointLight> light) override;
		void destroyCamera(std::shared_ptr<Camera> camera) override;
		void setModel(RenderObject* object, const std::string& path) override;

	private:
		std::unique_ptr<DXRenderBufferPool> _poolofObjects;
		std::unique_ptr<DXRenderBufferPool> _poolofPointLights;
		std::unique_ptr<DXRenderBufferPool> _poolofDirLights;

		DXRender* render;
		DXTextureFactory* textureFactory;
		std::unique_ptr<MeshFactory> meshFactory;


	};
}

