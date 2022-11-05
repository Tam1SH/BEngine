#include <vulkan.h>
#include <boost/filesystem.hpp>
#include <fstream>
export module Shader;
import <vector>;
namespace BEbraEngine {

	export struct AbstractShader {

		AbstractShader() { }

		virtual ~AbstractShader() { }
	};

    export struct VulkanShader : AbstractShader {

		VulkanShader() { }

		~VulkanShader() { }

		static VulkanShader* createFromFile(const VkDevice& device, const boost::filesystem::path& path)
        {
            //DEBUG_LOG1(path.string());
            std::ifstream file(path.string(), std::ios::ate | std::ios::binary);

            if (!file.is_open()) {
                //DEBUG_LOG1("failed to open file with path: " + path.string());
                throw std::runtime_error("");
            }

            size_t fileSize = (size_t)file.tellg();
            std::vector<char> buffer(fileSize);

            file.seekg(0);
            file.read(buffer.data(), fileSize);
            file.close();

            auto shader = new VulkanShader(buffer);
            shader->createModule(device);
            return shader;
        }
	

        
        



		std::vector<char> data;

		VkShaderModule module;

	private:
		VulkanShader(std::vector<char> data)
        {
            this->data = data;
        }

		void createModule(const VkDevice& device)
        {
            VkShaderModuleCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = data.size();
            createInfo.pCode = reinterpret_cast<const uint32_t*>(data.data());

            if (vkCreateShaderModule(device, &createInfo, nullptr, &module) != VK_SUCCESS) {
                //DEBUG_LOG1("failed to create shader module!");
                throw std::runtime_error("");
            }
        }
	};


}

