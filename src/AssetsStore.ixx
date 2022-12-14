module;
export module AssetsStore;
import Asset;
import Task;
import <string>;
export namespace BEbraEngine {
	struct Model;
	class TextureFactory;
	struct MeshFactory;
	struct Texture;
}

namespace BEbraEngine {

	export struct AssetsStore {

		Task<Asset<Model*>> getModel(const std::string& path);

		Task<Asset<Texture*>> getTexture(const std::string& path);

		void setBasePath(const std::string& path);

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