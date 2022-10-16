module;
#include <variant>
export module RenderDecl;
import VulkanRender;
namespace BEbraEngine {
	export using Render = std::variant<VulkanRender>;
}