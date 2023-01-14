module;
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

export module MeshFactory;
import RenderAllocator;
import Model;
import Texture;
import <fstream>;
import <map>;
import <string>;
import <vector>;
import <optional>;

using std::optional;
using std::shared_ptr;
using std::string;
using std::map;
using std::vector;


namespace BEbraEngine {
    export class TextureFactory;
}
namespace BEbraEngine {
    
    export struct MeshFactory {
    public:
        
        std::optional<Model*> create(const ModelCreateInfo& info);
        
        std::optional<Model*> createAsync(const ModelCreateInfo& info);

        std::shared_ptr<Model> getDefaultModel(const string& name);

        MeshFactory() {}
        MeshFactory(RenderAllocator& renderAlloc);

        MeshFactory(const MeshFactory&) = delete;
        MeshFactory operator=(const MeshFactory&) = delete;

        MeshFactory(MeshFactory&&) noexcept = default;
        MeshFactory& operator=(MeshFactory&&) noexcept = default;
    private:


        void downloadDefaultModels();
        
        void processNode(Model* model, aiNode* node, const aiScene* scene, const string& path);

        Mesh processMesh(Model* model, aiMesh* mesh, const aiScene* scene, const string& path);

        std::vector<Texture*> loadMaterialTextures(Model* model, aiMaterial* mat, aiTextureType type, string typeName, const string& path);

        TextureFactory* _textureFactory;

        RenderAllocator* renderAlloc;

        std::map<string, shared_ptr<Model>> default_models;
        
    };

}

