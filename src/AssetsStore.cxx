#include <string>
module AssetsStore;
namespace BEbraEngine {

	Task<Asset<Model*>> AssetsStore::getModel(const std::string& path)
	{
		return Task<Asset<Model*>>();
	}

	Task<Asset<Texture*>> AssetsStore::getTexture(const std::string& path)
	{
		return Task<Asset<Texture*>>();
	}

	void AssetsStore::setBasePath(const std::string& path)
	{
		basePath = path;
	}

	AssetsStore::AssetsStore(
		TextureFactory& textureFactory, 
		MeshFactory& meshFactory) : textureFactory(&textureFactory), meshFactory(&meshFactory)
	{
		//basePath = boost::filesystem::current_path().string();

	}
}