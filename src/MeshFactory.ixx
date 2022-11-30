module;
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <fstream>
#include "platform.hpp"
#include <variant>
#include <map>
#include <string>
#include <vector>
#include <optional>
export module MeshFactory;

import VulkanRenderAllocator;
import Model;
import Texture;

using std::optional;
using std::shared_ptr;
using std::string;
using std::map;
using std::vector;


namespace BEbraEngine {
    class TextureFactory;
}
namespace BEbraEngine {
    
    export class MeshFactory {
    public:
        
        std::optional<Model*> create(const ModelCreateInfo& info);
        
        std::optional<Model*> createAsync(const ModelCreateInfo& info);

        std::shared_ptr<Model> getDefaultModel(const string& name);

        MeshFactory() {}
        MeshFactory(std::variant<VulkanRenderAllocator>& renderAlloc);

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

        std::variant<VulkanRenderAllocator>* renderAlloc;

        std::map<string, shared_ptr<Model>> default_models;
        
    };

    namespace create {
        MeshFactory meshFactory(std::variant<VulkanRenderAllocator>& renderAlloc);
    }
    
}

