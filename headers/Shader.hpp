#pragma once
#include "stdafx.h"
#include "platform.hpp"

namespace BEbraEngine {

	class AbstractShader {
	public:

		AbstractShader() { }

		virtual ~AbstractShader() { }
	};

	class VulkanShader : public AbstractShader {
	public:
		VulkanShader() { }

		~VulkanShader() { }

		static VulkanShader* createFromFile(const VkDevice& device, const boost::filesystem::path& path);
	

		BE_STD::vector<char> data;

		VkShaderModule module;

	private:
		VulkanShader(BE_STD::vector<char> data);

		void createModule(const VkDevice& device);
	};


}

