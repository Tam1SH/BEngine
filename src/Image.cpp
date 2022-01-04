#include "stdafx.h"
#include "Image.hpp"
#include "VulkanRender.hpp"
#include "Debug.hpp"
namespace BEbraEngine {
    Texture::Texture()
    {
    }
    Texture::~Texture()
    {
        DEBUG_DESTROY_CHECK("texture has not destroyed", this, "", Debug::ObjectType::Empty, Debug::MessageType::Info);
    }
}