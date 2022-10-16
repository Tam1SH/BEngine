module;
#include "platform.hpp"
#include <tbb.h>
#include <variant>

export module RenderWorld;
import RenderDecl;
import Camera;
import DirectionLight;
import Light;
import RenderObject;
import RenderData;

import <vector>;
import <algorithm>;

namespace BEbraEngine {


    export struct RenderWorld {
        struct Request { };

        void selectMainCamera(SimpleCamera& camera);

        void addGlobalLight(DirectionLight& globalLight);

        void addCamera(SimpleCamera& camera);

        void removeCamera(SimpleCamera& camera);

        void removeObject(RenderObject& object);

        void addObject(RenderObject& object);

        void addLight(Light& light);

        void update();

        void updateState(const Request& request);

        RenderData& getRenderData();


        RenderWorld(Render& render);
        RenderWorld() {}
        
        
        RenderWorld(RenderWorld&& o) noexcept {
            data = std::move(o.data);
            requestQueue.clear();
            objects = std::move(o.objects);
            render = std::move(o.render);
        }

        RenderWorld& operator=(RenderWorld&& o) noexcept {

            data = std::move(o.data);
            requestQueue.clear();
            objects = std::move(o.objects);
            render = std::move(o.render);
            return *this;

        }

        RenderWorld(const RenderWorld&) noexcept = delete;
        RenderWorld& operator=(const RenderWorld&) noexcept = delete;

    private:
        RenderData* data;
        Render* render;

        tbb::concurrent_queue<Request> requestQueue{};
        std::vector<RenderObject*> objects;
        std::vector<Light*> lights;
    };
}

