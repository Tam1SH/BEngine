#include "stdafx.h"
#include "Pipeline.hpp"
namespace BEbraEngine {


	void VulkanPipeline::setViewports(const std::vector<VkViewport>& ports)
	{
		viewPorts = ports;
	}

	void VulkanPipeline::setVertexInputState(const VkPipelineVertexInputStateCreateInfo& info)
	{
		vertexInputState = info;
	}

	void VulkanPipeline::create(const VkDevice& device)
	{
		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = shaderStageCreateInfo.size();
		pipelineInfo.pStages = shaderStageCreateInfo.data();
		pipelineInfo.pVertexInputState = &vertexInputState;
		pipelineInfo.pInputAssemblyState = &inputAssemblyState;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizationState;
		pipelineInfo.pMultisampleState = &multisampleState;
		pipelineInfo.pColorBlendState = &colorBlendState;
		pipelineInfo.layout = layout;
		pipelineInfo.renderPass = pass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.pDepthStencilState = &depthStencilState;
		
		vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipe);
	}
	void VulkanPipeline::setVertexInputBindingDescription(const VkVertexInputBindingDescription& description)
	{
		vertexInputBindingDescription = description;
	}
	void VulkanPipeline::setViewportState(const VkPipelineViewportStateCreateInfo& info)
	{
		viewportState = info;
	}
	void VulkanPipeline::setRasterizationState(const VkPipelineRasterizationStateCreateInfo& info)
	{
		rasterizationState = info;
	}
	void VulkanPipeline::setMultisampleState(const VkPipelineMultisampleStateCreateInfo& info)
	{
		multisampleState = info;
	}
	void VulkanPipeline::setDepthStencilState(const VkPipelineDepthStencilStateCreateInfo& info)
	{
		depthStencilState = info;
	}
	void VulkanPipeline::setColorBlendState(const VkPipelineColorBlendStateCreateInfo& info)
	{
		colorBlendState = info;
	}
	void VulkanPipeline::setPushConstantRange(const VkPushConstantRange& range)
	{
		constantRange = range;
	}
	void VulkanPipeline::setColorBlendAttachments(std::vector<VkPipelineColorBlendAttachmentState> attachments)
	{
		colorBlendAttachments = attachments;
	}
	void VulkanPipeline::setScissors(const std::vector<VkRect2D> info)
	{
		scissors = info;
	}
	void VulkanPipeline::setShaderStages(const std::vector<VkPipelineShaderStageCreateInfo>& stages)
	{
		shaderStageCreateInfo = stages;
	}
	void VulkanPipeline::setShaders(const std::vector<VulkanShader*> shaders)
	{
		cacheShaders = shaders;
	}
	void VulkanPipeline::setPipelineCreateInfo(const VkPipelineLayout& info)
	{
		layout = info;
	}
	void VulkanPipeline::setPipelineLayout(const VkPipelineLayout& layout)
	{
		this->layout = layout;
	}
	void VulkanPipeline::setInputAssemblyState(const VkPipelineInputAssemblyStateCreateInfo& info)
	{
		inputAssemblyState = info;
	}
	void VulkanPipeline::setRenderPass(const VkRenderPass& pass)
	{
		this->pass = pass;
	}
}
