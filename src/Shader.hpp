#pragma once
#include "stdafx.h"
namespace BEbraEngine {

	class AbstractShader {
	public:

		AbstractShader() { }

		virtual ~AbstractShader() { }
	};

	class VulkanShader : public AbstractShader
	{
	public:
		VulkanShader() { }

		~VulkanShader() { }

		static VulkanShader* createFromFile(const VkDevice& device, const boost::filesystem::path& path);
	

		std::vector<char> data;

		VkShaderModule module;

	private:
		VulkanShader(std::vector<char> data);

		void createModule(const VkDevice& device);
	};


}

