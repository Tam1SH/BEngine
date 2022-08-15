#include "platform.hpp"


#include <tbb.h>

#define DEBUG_LOG1(msg) BEbraEngine::Debug::log(__LINE__, __FILE__, msg);
#define DEBUG_LOG2(msg, pointer, name, oType, mType) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer, name, oType, mType)
#define DEBUG_LOG3(msg, pointer) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer);

#ifdef _DEBUG
#define DEBUG_DESTROY_CHECK_DECL() public: bool isDestroyed; private:
#define DEBUG_DESTROY_CHECK(msg, pointer, name, oType, mType) if(!isDestroyed) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer, name, oType, mType)	

#else
#define DEBUG_DESTROY_CHECK(msg, pointer, name, oType, mType) 
#define DEBUG_DESTROY_CHECK_DECL()
#endif


export module RenderWorld;
import Render;
import RenderObjects;
import Debug;
import RenderData;
import <vector>;
import <algorithm>;


namespace BEbraEngine {

    export class RenderWorld {
    public:
        struct Request { };
    public:

        RenderWorld(Render& render);

        void removeObject(const RenderObject& object);

        void addObject(RenderObject& object);

        void addLight(Light& light);

        void update();

        void updateState(const Request& request);

        RenderData& getRenderData();
        
    private:
        RenderData* data;

        tbb::concurrent_queue<Request> requestQueue;
        std::vector<RenderObject*> objects;
        std::vector<Light*> lights;
        Render* render;
    };
}

