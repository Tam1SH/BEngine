#include <variant>
#include <tbb.h>
#include <vector>
#include <algorithm>

export module RenderWorld;

namespace BEbraEngine {
    export class SimpleCamera;
    export class DirectionLight;
    export struct RenderObject;
    export class Light;
    export struct Render;
    export struct RenderData;
}

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

        tbb::concurrent_queue<Request> requestQueue;
        std::vector<RenderObject*> objects;
        std::vector<Light*> lights;
    };
}

