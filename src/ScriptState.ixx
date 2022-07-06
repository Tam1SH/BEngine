
#include <boost/filesystem.hpp>
#include "platform.hpp"
#include <tbb.h>
export module ScriptState;
import AbstractRender;
import ExecuteQueues;
import <queue>;
import <memory>;
import <functional>;
import <list>;
import <vector>;
import <optional>;
import <string>;
import BaseRenderWindow;
import RenderObjects;
import Vector4;
import Vector3;

import GameObject;
import Camera;
using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;
using std::function;
using std::vector;
using std::list;



namespace BEbraEngine {
    export class Physics;
    class ObjectFactoryFacade;
    class ScriptManager;

}

namespace BEbraEngine {
    
    export class ScriptState {
    public:

        ScriptState(AbstractRender& render, Physics& physics, BaseWindow& window);

        void scriptInit();

        void clearObjects();

        void fixedUpdate();

        void update();

        void updateState();

        void addObject(shared_ptr<GameObject> object);

        void removeObject(shared_ptr<GameObject> object, function<void(GameObject&)> callback);

        void addCamera(SimpleCamera& camera);

        void addLight(Light& light);

        void addDirLight(DirectionLight& light);

        ~ScriptState();

        

    private:

        BaseWindow* window;

        vector<shared_ptr<GameObject>> objects_;

        vector<shared_ptr<Light>> lights;

        tbb::concurrent_hash_map<const GameObject*, shared_ptr<GameObject>> objectsCache;

        ExecuteQueues<function<void()>> queues;

        AbstractRender* render;

        Physics* physics;
        
        unique_ptr<RenderWorld> renderWorld;

        unique_ptr<ObjectFactoryFacade> scriptObjectFactory;

        unique_ptr<ScriptManager> scriptManager;



        shared_ptr<SimpleCamera> camera;

        shared_ptr<DirectionLight> globalLight;

        shared_ptr<Light> light;

        shared_ptr<GameObject> sphere;

        shared_ptr<GameObject> player;

        list<shared_ptr<GameObject>> bounds;
        list<shared_ptr<GameObject>> objects;
        Vector3 scale;
        Vector3 rotate;
        Vector3 lightColor;
        int step;
        bool addred = true;
        bool addblue;
        bool addgreen;

        bool lookatobject;
        Vector3* posofobject;

        Vector3* pos;
        Vector3* direction;
    };
}
