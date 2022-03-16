#include "stdafx.h"
#include "Texture.hpp"
#include "VulkanRender.hpp"
#include "Debug.hpp"
#include "IVisitorGameComponentDestroyer.hpp"
namespace BEbraEngine {
    Texture::Texture()
    {
    }
    Texture::~Texture()
    {
        DEBUG_DESTROY_CHECK("texture has not destroyed", this, "", Debug::ObjectType::Empty, Debug::MessageType::Info);
    }
    void Texture::destroy(IVisitorGameComponentDestroyer& destroyer)
    {
        destroyer.destroyTextureComponent(*this);
    }
}