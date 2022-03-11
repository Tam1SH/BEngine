#pragma once
#include "stdafx.h"

#include "AbstractRender.hpp"


namespace BEbraEngine {

    class RenderWorld {
    public:

        RenderWorld(AbstractRender& render) {
            this->render = &render;
        }


        void removeObject(RenderObject& object) {
            auto iter = std::remove(objects.begin(), objects.end(), &object);
            objects.erase(iter);
            RenderData data;
            data.objects = objects;
            data.lights = lights;
            render->updateState(data);
        }

        void addObject(RenderObject& object) {
            objects.push_back(&object);
            RenderData data;
            data.objects = objects;
            data.lights = lights;
            render->updateState(data);

        }

        void addLight(Light& light) {
            lights.push_back(&light);
            RenderData data;
            data.objects = objects;
            data.lights = lights;
            render->updateState(data);
        }

        void updateRenderData();

        
    private:
        vector<RenderObject*> objects;
        vector<Light*> lights;
        AbstractRender* render;
    };
}

