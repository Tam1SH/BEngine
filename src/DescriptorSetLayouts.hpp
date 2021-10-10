#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <string>

//TODO: � ���� ��� ����� ��� � ���� ������, �� ���� ��-�� � ���� ������ 
class DescriptorSetLayouts
{
public:
	struct DescriptorSetLayout {
		VkDescriptorSetLayout layout;
		std::vector<VkDescriptorSetLayoutBinding> info;
		std::string name;
	};
private:
	VkDevice device;
	std::vector<DescriptorSetLayout> layouts;
public:
	std::unique_ptr<std::vector<VkDescriptorSetLayout>> Get() { 
		auto ls = new std::vector<VkDescriptorSetLayout>();
		ls->resize(layouts.size());
		for (int i = 0; i < layouts.size(); i++) {
			ls->at(i) = layouts[i].layout;
		}
		return std::unique_ptr<std::vector<VkDescriptorSetLayout>>(ls);
	}
	std::vector<DescriptorSetLayout> GetLayouts() {
		return layouts;
	}
	void Create(VkDevice device) {
		this->device = device;
	}

	void AddLayout(VkDescriptorSetLayout layout, std::vector<VkDescriptorSetLayoutBinding> info = {}) {
		layouts.push_back({ layout, info });
	}

	void CreateLayout(std::vector<VkDescriptorSetLayoutBinding>& bindingInfo) {
		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindingInfo.size());
		layoutInfo.pBindings = bindingInfo.data();
		
		VkDescriptorSetLayout layout;
		if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &layout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}
		AddLayout(layout, bindingInfo);
	}

	void DeleteLayout(VkDescriptorSetLayout layout) {
		std::remove_if(layouts.begin(), layouts.end(), 
			[&](DescriptorSetLayout lay) {
				return layout == lay.layout; 
			});
	}



};


