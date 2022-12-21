#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb-master/stb_image.h>
#include <stb-master/stb_image_write.h>
#include <tbb.h>
module TextureLoader;
import Logger;
namespace BEbraEngine {

	Task<optional<TextureData>> TextureLoader::createAsync(const TextureLoadInfo& info)
	{
		Task<optional<TextureData>> task{};
		stbi_set_flip_vertically_on_load(info.flip);
		
		tbb::task_arena{}.enqueue([=] {
			int texWidth, texHeight, texChannels;
			stbi_uc* rows = stbi_load(info.path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
			task.execute(std::make_optional<TextureData>({ texWidth, texHeight, texChannels, rows }), true);
		});

		return task;
	}
	void TextureLoader::free(const TextureData& data)
	{
		if (data.data)
			stbi_image_free(data.data);
		else
			Logger::warn("data is empty");

	}
}