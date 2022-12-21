export module TextureData;

namespace BEbraEngine {

	export struct TextureData {
		int width, height, channels;
		unsigned char* data{};
	};

	export struct CreateTextureInfo {
		const TextureData& data;
		bool generateMip = false;
	};

}