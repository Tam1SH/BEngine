module;
#include <variant>
export module RenderAllocatorDecl;
import VulkanRenderAllocator;
namespace BEbraEngine {
	export using RenderAllocator = std::variant<VulkanRenderAllocator>;
}