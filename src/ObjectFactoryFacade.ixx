module;
#include <memory>;
#include <string>;
export module ObjectFactoryFacade;
import GameObjectFactory;
import Light;
import Camera;
import Transform;
import Material;
import DirectionLight;
import GameObject;
import Collider;
import GameComponent;

import GameComponentCreateInfo;
import Vector3;



using std::shared_ptr; 
using std::unique_ptr;
using std::string;

namespace BEbraEngine {
    //export class GameObjectFactory;
    export struct ScriptState;
}

namespace BEbraEngine {

    export struct ObjectFactoryFacade {
        
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
        
        void setCollider(Collider& col, ColliderType& type) 
        {
            realFactory_->setCollider(col, type);
        }

        void setContext(ScriptState* logic);

        void destroyComponent(GameComponent& component);

        ObjectFactoryFacade(const ObjectFactoryFacade&) noexcept = delete;
        ObjectFactoryFacade& operator=(const ObjectFactoryFacade&) noexcept = delete;

        ObjectFactoryFacade(ObjectFactoryFacade&&) noexcept = default;
        ObjectFactoryFacade& operator=(ObjectFactoryFacade&&) noexcept = default;

        ObjectFactoryFacade() {}

        ObjectFactoryFacade(GameObjectFactory* factory);
        

    private:
        GameObjectFactory* realFactory_{};
        ScriptState* state_{};
        
    };
    
}
