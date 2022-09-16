module;
#include <boost/filesystem.hpp>

export module AssetsStore;
import TextureFactoryDecl;
import Texture;
import Material;
import MeshFactory;
import Asset;
import Task;
import <string>;



namespace BEbraEngine {

	export class AssetsStore {
	public:

		Task<Asset<Texture>> getTexture(const std::string& path);

		AssetsStore() {}

		AssetsStore(
			TextureFactory& textureFactory,
			MeshFactory& meshFactory);

	private:
		TextureFactory* textureFactory;
		MeshFactory* meshFactory;
		std::string basePath;
	};
}