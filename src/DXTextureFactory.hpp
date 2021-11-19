#pragma once
#include "ITextureFactory.hpp"
namespace BEbraEngine {
	class AbstractRender;
	class DXRender;
}

namespace BEbraEngine {

	class DXTextureFactory : public ITextureFactory
	{
	public:
		virtual Texture* createAsync(const std::string& path) override;
		virtual Texture* create(const std::string& path) override;
		virtual Texture* createEmpty() override;

		DXTextureFactory(AbstractRender* render);
		~DXTextureFactory();
	private:
		DXRender* render;
	};

}
