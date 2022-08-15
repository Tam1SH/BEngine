#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <boost/filesystem.hpp>

#include <fstream>
#include "platform.hpp"

export module MeshFactory;
import <map>;
import <string>;
import <vector>;
import <optional>;
using std::optional;
using std::shared_ptr;
using std::string;
using std::map;
using std::vector;
import Render;
import Model;
import Texture;

namespace BEbraEngine {
    //class Render;
    class TextureFactory;
}
namespace BEbraEngine {
    
    export class MeshFactory {
    public:
        
        std::optional<Model*> create(const ModelCreateInfo& info);
        
        std::optional<Model*> createAsync(const ModelCreateInfo& info);

        std::shared_ptr<Model> getDefaultModel(const string& name);

        MeshFactory(Render* render);
    private:


        void downloadDefaultModels();
        
        void processNode(Model* model, aiNode* node, const aiScene* scene, const string& path);

        Mesh processMesh(Model* model, aiMesh* mesh, const aiScene* scene, const string& path);

        std::vector<Texture*> loadMaterialTextures(Model* model, aiMaterial* mat, aiTextureType type, string typeName, const string& path);

        TextureFactory* _textureFactory;

        Render* render;

        std::map<string, shared_ptr<Model>> default_models;
        
    };
    
    
}

