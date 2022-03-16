#pragma once
#include "stdafx.h"

#include "AbstractRender.hpp"
#include "Debug.hpp"
namespace BEbraEngine {

    class RenderWorld {
    public:
        struct Request { };
    public:

        RenderWorld(AbstractRender& render) {
            this->render = &render;
        }


        void removeObject(const RenderObject& object) {
            auto iter = std::remove(objects.begin(), objects.end(), &object);
            if (iter != objects.end()) {
                objects.erase(iter);
                updateState({});
            }
            else {
                DEBUG_LOG1("Object has not been in renderWorld", &object);
                throw std::exception();
            }
            
        }

        void addObject(RenderObject& object) {
            objects.push_back(&object);
            updateState({});

        }

        void addLight(Light& light) {
            lights.push_back(&light);
            updateState({});
        }

        void update();

        void updateState(const Request& request);
        
    private:
        
        tbb::concurrent_queue<Request> requestQueue;
        vector<RenderObject*> objects;
        vector<Light*> lights;
        AbstractRender* render;
    };
}

