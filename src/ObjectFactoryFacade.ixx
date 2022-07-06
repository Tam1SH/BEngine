#include "platform.hpp"
#include <boost/filesystem.hpp>


export module ObjectFactoryFacade;
import <memory>;
import <string>;
import RenderObjects;
import Camera;
import GameComponentCreateInfo;
import GameComponent;
import Vector3;
import Collider;
import GameObject;
using std::shared_ptr; 
using std::unique_ptr;
using std::string;


namespace BEbraEngine {
    export class GameObjectFactory;
    export class ScriptState;
}

namespace BEbraEngine {

    export class ObjectFactoryFacade {
    public:
        
        shared_ptr<GameObject> create(const Vector3& position);

        shared_ptr<Light> createLight(const Vector3& position);

        shared_ptr<DirectionLight> createDirLight(const Vector3& direction);

        void setMaterialAsync(shared_ptr<GameObject> object, const MaterialCreateInfo& info);

        void destroy(shared_ptr<GameObject> object);

        void destroy(GameComponent& object);

        void destroyPointLight(Light& light);

        shared_ptr<SimpleCamera> createCamera(const Vector3& position);

        void destroyCamera(SimpleCamera& camera);

        void setModel(GameObject& object, const string& path);
        
        void setCollider(Collider& col, ColliderType type);

        void setContext(ScriptState* logic);

        void destroyComponent(GameComponent& component);

        ObjectFactoryFacade() {}

        ObjectFactoryFacade(GameObjectFactory* factory);
        

    private:
        GameObjectFactory* realFactory_{};
        ScriptState* state_{};
        
    };
    
}
