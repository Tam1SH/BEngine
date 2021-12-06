#include "stdafx.h"
#include "DXTextureFactory.hpp"
#include "Image.hpp"
#include "DXRender.hpp"
namespace BEbraEngine {

	Texture* DXTextureFactory::createAsync(const std::filesystem::path& path, std::function<void(Texture*)>)
	{
		return nullptr;
	}

	Texture* DXTextureFactory::create(const std::string& path)
	{
		return nullptr;
	}

	Texture* DXTextureFactory::createEmpty()
	{
		return nullptr;
	}

	DXTextureFactory::DXTextureFactory(AbstractRender* render)
	{
		this->render = dynamic_cast<DXRender*>(render);
	}

	DXTextureFactory::~DXTextureFactory()
	{
	}

}