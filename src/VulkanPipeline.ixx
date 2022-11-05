#include <vulkan.h>
export module VulkanPipeline;
import Shader;
import <vector>;

namespace BEbraEngine {

	
	export struct VulkanPipeline
	{
		VkPipeline& getPipeLine() { return pipe; }

		void setViewports(const std::vector<VkViewport>& ports);

		void setVertexInputState(const VkPipelineVertexInputStateCreateInfo& info);

		void create(const VkDevice& device);

		void setVertexInputBindingDescription(const VkVertexInputBindingDescription& description);

		void setViewportState(const VkPipelineViewportStateCreateInfo& info);

		void setRasterizationState(const VkPipelineRasterizationStateCreateInfo& info);

		void setMultisampleState(const VkPipelineMultisampleStateCreateInfo& info);

		void setDepthStencilState(const VkPipelineDepthStencilStateCreateInfo& info);

		void setColorBlendState(const VkPipelineColorBlendStateCreateInfo& info);

		void setPushConstantRange(const VkPushConstantRange& range);

		void setColorBlendAttachments(const std::vector<VkPipelineColorBlendAttachmentState> attachments);

		void setScissors(const std::vector<VkRect2D> scissors);

		void setShaderStages(const std::vector<VkPipelineShaderStageCreateInfo>& stages);

		void setShaders(const std::vector<VulkanShader*> shaders);

		void setPipelineCreateInfo(const VkPipelineLayout& info);
		
		void setPipelineLayout(const VkPipelineLayout& layout);

		void setInputAssemblyState(const VkPipelineInputAssemblyStateCreateInfo& info);

		void setRenderPass(const VkRenderPass& pass);
	private:
		VkPipeline pipe{};

		VkRenderPass pass{};
		VkPipelineVertexInputStateCreateInfo vertexInputState{};
		VkVertexInputBindingDescription vertexInputBindingDescription{};
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyState{};
		VkPipelineViewportStateCreateInfo viewportState{};
		VkPipelineRasterizationStateCreateInfo rasterizationState{};
		VkPipelineMultisampleStateCreateInfo multisampleState{};
		VkPipelineDepthStencilStateCreateInfo depthStencilState{};
		VkPipelineColorBlendStateCreateInfo colorBlendState{};
		VkGraphicsPipelineCreateInfo pipelineLayout{};
		VkPipelineLayout layout{};
		VkPushConstantRange constantRange{};
		std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
		std::vector<VkViewport> viewPorts;
		std::vector<VkRect2D> scissors;
		std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfo;
		std::vector<VulkanShader*> cacheShaders;
	};

}

