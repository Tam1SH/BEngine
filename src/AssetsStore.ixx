module;
#include <string>
export module AssetsStore;
import Asset;
import Task;

export namespace BEbraEngine {
	class Model;
	class TextureFactory;
	class MeshFactory;
	class Texture;
}

namespace BEbraEngine {

	export class AssetsStore {
	public:

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