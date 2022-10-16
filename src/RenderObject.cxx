module RenderObject;
import Transform;
import RenderBuffer;
//import GameComponentDestroyer;

namespace BEbraEngine {

    void RenderObject::destroy(GameComponentDestroyer& destroyer) {
        //destroyer.destroyRenderComponent(*this);

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