#pragma once
#include <vulkan/vulkan.h>
#include "VkBuffer.hpp"
#include "BaseVulkanRender.hpp"
//TODO: загрузка моделей и присваивание примитивов
namespace BEbraEngine {
	class Mesh1
	{
	public:
		Buffer VBO;
		Buffer EBO;
		Mesh1() {}
		Mesh1(Buffer VBO, Buffer EBO) : VBO(std::move(VBO)), EBO(std::move(EBO)) {}

		~Mesh1() {
			//VBO.Destroy();
			//EBO.Destroy();
		}
	};

}