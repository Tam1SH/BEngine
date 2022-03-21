#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "RenderObject.hpp"
namespace BEbraEngine {
    class AbstractRender;
    class RenderObject;
    class Light;
    class RenderData;
}

BE_NAMESPACE_STD_BEGIN
    template<class T, class Alloc>
    class vector;
BE_NAMESPACE_STD_END


namespace BEbraEngine {

    class RenderWorld {
    public:
        struct Request { };
    public:

        RenderWorld(AbstractRender& render);

        void removeObject(const RenderObject& object);

        void addObject(RenderObject& object);

        void addLight(Light& light);

        void update();

        void updateState(const Request& request);

        RenderData& getRenderData();
        
    private:
        RenderData* data;

        tbb::concurrent_queue<Request> requestQueue;
        vector<RenderObject*> objects;
        vector<Light*> lights;
        AbstractRender* render;
    };
}

