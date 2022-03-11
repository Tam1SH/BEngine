#include "stdafx.h"
#include "RenderObject.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "VkBuffer.hpp"
#include "IVisitorGameComponentDestroyer.hpp"
namespace BEbraEngine {
    void RenderObject::update()
    {
        ShaderData data;
        data.model = transform->getBasis();
        data.color = _color;
        matrix->setData(&data, sizeof(ShaderData));
    }

    RenderObject::~RenderObject()
    {
        DEBUG_DESTROY_CHECK("RenderObject has not destroyed", this, "", Debug::ObjectType::RenderObject, Debug::MessageType::Info);
    }

    RenderObject::RenderObject()
    {
    }

    void RenderObject::release()
    {
    }

    

    void Light::release()
    {
        ShaderData _data;
        _data.position = Vector3();
        _data.ambient = Vector3();
        _data.diffuse = Vector3();
        _data.specular = Vector3();
        _data.constant = 1.0f;
        _data.linear = 0;
        _data.quadratic = 0;
        data->setData(&_data, sizeof(ShaderData));
    }

    void Light::update()
    {
        ShaderData _data;
        _data.position = transform->getPosition();
        _data.ambient = color;
        _data.diffuse = color;
        _data.specular = color;
        _data.constant = 1.f;
        _data.linear = 0.022f;
        _data.quadratic = 0.0019f;
        data->setData(&_data, sizeof(ShaderData));

    }

    void Light::destroy(IVisitorGameComponentDestroyer& destroyer)
    {
        destroyer.destroyPointLightComponent(*this);
    }

    void RenderObject::destroy(IVisitorGameComponentDestroyer& destroyer)
    {
        destroyer.destroyRenderComponent(*this);
    }

    void DirectionLight::destroy(IVisitorGameComponentDestroyer& destroyer)
    {
        destroyer.destroyDirectionLightComponent(*this);
    }

    Line::~Line()
    {
        
    }

    void Line::create(AbstractRender& render)
    {
    }
    void Line::update()
    {
        _data = { from, to, color };

    }

    Material::Material(Texture* ambient, Texture* specular, Texture* normal)
    {

    }

    void Material::destroy(IVisitorGameComponentDestroyer& destroyer)
    {
        destroyer.destroyMaterialComponent(*ambient);
        destroyer.destroyMaterialComponent(*specular);
        destroyer.destroyMaterialComponent(*normal);
    }

}


