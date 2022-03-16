#include "stdafx.h"
#include "RenderWorld.hpp"
#include "RenderObject.hpp"
namespace BEbraEngine {


    void RenderWorld::update()
    {

        for (auto& light : lights) {
            light->update();
        }
        for(auto& object : objects)
            object->update();

        Request req;
        if (requestQueue.try_pop(req)) {
            RenderData data;
            data.objects = objects;
            data.lights = lights;
            render->updateState(data);
        }
    }

    void RenderWorld::updateState(const Request& request)
    {
        requestQueue.push(request);

    }

}