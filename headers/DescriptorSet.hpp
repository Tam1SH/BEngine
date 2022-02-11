#pragma once
#include "stdafx.h"
class DescriptorSet
{
public:
	operator VkDescriptorSet* () { return &_set; }
	operator const VkDescriptorSet& () { return _set; }
	size_t getOffset() { return _offset; }
	size_t getSize() { return _size; }
private:
	size_t _offset;
	size_t _size;
	VkDescriptorSet _set;
};

