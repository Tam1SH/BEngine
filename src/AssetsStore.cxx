#include <boost/filesystem.hpp>
module AssetsStore;
namespace BEbraEngine {
	Task<Asset<Texture>> AssetsStore::getTexture(const std::string& path)
	{
		return Asset<Texture>();
	}

	AssetsStore::AssetsStore(
		TextureFactory& textureFactory, 
		MeshFactory& meshFactory) : textureFactory(&textureFactory), meshFactory(&meshFactory)
	{
		basePath = boost::filesystem::current_path().string();

	}
}