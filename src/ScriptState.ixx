module;
export module ScriptState;
import Vector4;
import Vector3;
//import ExecuteQueues;
import <variant>;
import <queue>;
import <memory>;
import <functional>;
import <list>;
import <vector>;
import <optional>;
import <string>;

using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;
using std::function;
using std::vector;
using std::list;

namespace BEbraEngine {
    export struct Physics;
    export struct ObjectFactoryFacade;
    export struct Render;
    export struct RenderObject;
    export struct SimpleCamera;
    export struct Light;
    export struct GameObject;
    export struct DirectionLight;
    export struct RenderWorld;
    export struct ScriptManager;
    export template<typename T>
    struct ExecuteQueues;

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

        ScriptState(Render& render, Physics& physics, 
                    RenderWorld& renderWorld, ScriptManager& manager, ObjectFactoryFacade& objectFactory);
        ScriptState() {}

        ScriptState(ScriptState&&) noexcept = default;
        ScriptState& operator=(ScriptState&&) noexcept = default;
        ScriptState(const ScriptState&) noexcept = delete;
        ScriptState& operator=(const ScriptState&) noexcept = delete;

        ~ScriptState();

    private:

        vector<shared_ptr<GameObject>> objects_;

        vector<shared_ptr<Light>> lights;

        //ExecuteQueues<function<void()>> queues;

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
