export module Light_impl;
import Light;
import RenderBufferView;
namespace BEbraEngine {

    void Light::update()
    {
        ShaderData _data;
        _data.position = transform->getPosition();
        _data.color = color;
        _data.diffuse = color;
        _data.specular = color;
        _data.constant = 1.f;
        _data.linear = 0.022f;
        _data.quadratic = 0.0019f;
        data->setData(&_data, sizeof(ShaderData), 0);

    }
}