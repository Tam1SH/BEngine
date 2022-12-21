export module TextureLoader;
import Task;
import stdDeclaration;
import TextureData;
import <string>;

namespace BEbraEngine {
	struct TextureLoadInfo;
}

namespace BEbraEngine {

	export struct TextureLoader {

		virtual Task<optional<TextureData>> createAsync(const TextureLoadInfo& info);

		virtual void free(const TextureData& data);

	};

	export struct TextureLoadInfo {
		string path;
		bool flip = false;
	};
}
