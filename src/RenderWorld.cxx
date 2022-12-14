#include <tbb.h>
#include <exception>
module RenderWorld;
import CRender;
import RenderData;
import RenderObject;
import Light;
import <variant>;

namespace BEbraEngine {

    RenderWorld::RenderWorld(Render& render)
        : render(&render) {
        data = new RenderData;
    }

    void RenderWorld::selectMainCamera(SimpleCamera& camera)
    {
        data->mainCamera = &camera;
    }

    void RenderWorld::addGlobalLight(DirectionLight& globalLight)
    {
        throw std::exception("not implemented");
    }

    void RenderWorld::addCamera(SimpleCamera& camera)
    {
        throw std::exception("not implemented");
    }

    /*
    void RenderWorld::removeObject(RenderObject& object)
    {
            auto iter = std::remove(objects.begin(), objects.end(), &object);
            if (iter != objects.end()) {
                objects.erase(iter);
                updateState({});
            }
            else {
                            //DEBUG_LOG3("Object has not been in renderWorld", &object);
                throw std::exception();
            }

    }
    */
    void RenderWorld::removeCamera(SimpleCamera& camera)
    {
        throw std::exception("not implemented");
    }

    void RenderWorld::removeObject(RenderObject& object)
    {
        throw std::exception("not implemented");
    }



    void RenderWorld::addObject(RenderObject& object)
    {
        //objects.push_back(&object);
        updateState({});

    }

    void RenderWorld::addLight(Light& light)
    {
        lights.push_back(&light);
        updateState({});
    }

    void RenderWorld::update()
    {
        throw std::exception("not implemented");

        for (auto& light : lights) {
            light->update();
        }
        for (auto& object : objects)
            object->update();


        Request req;
        if (requestQueue.try_pop(req)) {
            RenderData data;
            data.objects = objects;
            data.lights = lights;
          //  render->updateState(data);
            requestQueue.clear();
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