#include "stdafx.h"
#include "RenderWorld.hpp"
#include "RenderObject.hpp"
#include "AbstractRender.hpp"
#include "RenderObject.hpp"
#include "Debug.hpp"
namespace BEbraEngine {
    RenderWorld::RenderWorld(AbstractRender& render)
    {
        this->render = &render;
        data = new RenderData();
    }
    void RenderWorld::removeObject(const RenderObject& object)
    {
        auto iter = std::remove(objects.begin(), objects.end(), &object);
        if (iter != objects.end()) {
            objects.erase(iter);
            updateState({});
        }
        else {
            DEBUG_LOG3("Object has not been in renderWorld", &object);
            throw std::exception();
        }

    }
    void RenderWorld::addObject(RenderObject& object)
    {
        objects.push_back(&object);
        updateState({});

    }
    void RenderWorld::addLight(Light& light)
    {
        lights.push_back(&light);
        updateState({});
    }
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
          //  requestQueue.clear();
        }
    }

    void RenderWorld::updateState(const Request& request)
    {
        requestQueue.push(request);

    }

    RenderData& RenderWorld::getRenderData()
    {
        *data = RenderData();
        data->lights = lights;
        data->objects = objects;
        return *data;
    }

}