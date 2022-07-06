#include <boost/filesystem.hpp>
module RenderObjects;
import Transform;
namespace BEbraEngine {
	void Line::create(AbstractRender& render) {

	}
    
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
	void RenderObject::update()
    {
        ShaderData data;
        data.model = transform->getBasis();
        data.color = _color;
        data.hasMaps = hasMaps;
        matrix->setData(&data, sizeof(ShaderData), 0);
    }
    
}