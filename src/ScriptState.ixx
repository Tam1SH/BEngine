module;
#include <variant>
#include <queue>
#include <memory>
#include <functional>
#include <list>
#include <vector>
#include <optional>
#include <string>
export module ScriptState;
import Vector4;
import Vector3;
import ExecuteQueues;

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;
using std::function;
using std::vector;
using std::list;

namespace BEbraEngine {
    export struct ObjectFactoryFacade;
    struct Physics;
    export struct Render;
    export struct RenderObject;
    export class SimpleCamera;
    export class Light;
    export class GameObject;
    export class DirectionLight;
    export struct ScriptManager;
    export struct RenderWorld;
    export class RenderAllocator;
}

namespace BEbraEngine {
    
    export struct ScriptState {

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

        ScriptState(Render& render, RenderAllocator& allocator, Physics& physics);
        ScriptState() {}

        ScriptState(ScriptState&&) noexcept = default;
        ScriptState& operator=(ScriptState&&) noexcept = default;
        ScriptState(const ScriptState&) noexcept = delete;
        ScriptState& operator=(const ScriptState&) noexcept = delete;

        ~ScriptState();

    private:

        vector<shared_ptr<GameObject>> objects_;

        vector<shared_ptr<Light>> lights;

        ExecuteQueues<function<void()>> queues;

        Render* render;

        Physics* physics;
        
        RenderWorld* renderWorld;

        ObjectFactoryFacade* scriptObjectFactory;

        ScriptManager* scriptManager;

        //std::unique_ptr<RenderObjectFactory> factory;

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
