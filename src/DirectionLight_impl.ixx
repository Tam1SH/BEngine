export module DirectionLight_impl;
import DirectionLight;
import RenderBufferView;
namespace BEbraEngine {
    void DirectionLight::update()
    {
        ShaderData data1;
        data1.direction = _direction;
        data1.color = color;
        data1.diffuse = color;
        data1.specular = color;
        data->setData(&data1, sizeof(ShaderData), 0);
    }
}