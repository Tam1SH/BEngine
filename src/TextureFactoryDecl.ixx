#include <variant>
export module TextureFactoryDecl;
import VulkanTextureFactory;

export namespace BEbraEngine {
	using TextureFactory = std::variant<VulkanTextureFactory>;
}