module;
#include <variant>
#include <memory>
#include <string>
#include <optional>
export module CRenderObjectFactory;
import Task;
import Vector3;


using std::shared_ptr;
using std::string;
using std::optional; 

namespace BEbraEngine {
    export class RenderObject;
    export class Light;
    export class SimpleCamera;
    export class RenderObjectCreateInfo;
    export class MaterialCreateInfo;
    export class Material;
    export class Transform;
    //export class TextureFactory;
    //export class VisitorGameComponentDestroyer;
    export class DirectionLight;
}

namespace BEbraEngine {
    export template<typename T>
        concept CRenderObjectFactory = requires(

            /*optional<Material*> createMaterialAsync*/ shared_ptr<RenderObject> shared_obj, const MaterialCreateInfo& mat_info,

            /*optional<RenderObject*> create*/ const RenderObjectCreateInfo& render_info,

            /*void setMaterial*/ RenderObject& obj, Material& material,

            /*void setComponentDestroyer*/ //VisitorGameComponentDestroyer& destroyer,

            /*void bindTransform*/ Light& light, Transform& transform,

            /*void bindTransform*/ RenderObject& object, Transform& transform_,

            /*Light* createLight*/ const Vector3& color, const Vector3& position,

            /*DirectionLight* createDirLight*/ const Vector3& color_, const Vector3& direction,

            /*SimpleCamera* createCamera*/ const Vector3& position_,

            /*void destroyObject*/ RenderObject& object_,

            /*void destroyPointLight*/ Light& light_,

            /*void destroyCamera*/ SimpleCamera& camera,

            /*void setModel*/ RenderObject& object__, const string& path,

            /* this */
            T& self
            )
    {
        //{ self.getTextureFactory() } -> std::same_as<TextureFactory&>;
        { self.createMaterialAsync(shared_obj, mat_info) } -> std::same_as<Task<optional<Material*>>>;
        { self.create(render_info) } -> std::same_as<optional<RenderObject*>>;
        { self.setMaterial(obj, material) } -> std::same_as<void>;
        //{ self.setComponentDestroyer(destroyer) } -> std::same_as<void>;
        { self.bindTransform(light, transform) } -> std::same_as<void>;
        { self.bindTransform(object, transform_) } -> std::same_as<void>;
        { self.createLight(color, position) } -> std::same_as<Light*>;
        { self.createDirLight(color_, direction) } -> std::same_as<DirectionLight*>;
        { self.createCamera(position_) } -> std::same_as<SimpleCamera*>;
        { self.destroyObject(object_) } -> std::same_as<void>;
        { self.destroyPointLight(light_) } -> std::same_as<void>;
        { self.destroyCamera(camera) } -> std::same_as<void>;
        { self.setModel(object__, path) } -> std::same_as<void>;
    };
}