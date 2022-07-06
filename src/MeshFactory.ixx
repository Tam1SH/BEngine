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
import AbstractRender;
import Model;
import Texture;

namespace BEbraEngine {
    //class AbstractRender;
    class ITextureFactory;
}
namespace BEbraEngine {
    
    export class MeshFactory {
    public:
        
        std::optional<Model*> create(const ModelCreateInfo& info);
        
        std::optional<Model*> createAsync(const ModelCreateInfo& info);

        std::shared_ptr<Model> getDefaultModel(const string& name);

        MeshFactory(AbstractRender* render);
    private:


        void downloadDefaultModels();
        
        void processNode(Model* model, aiNode* node, const aiScene* scene, const string& path);

        Mesh processMesh(Model* model, aiMesh* mesh, const aiScene* scene, const string& path);

        std::vector<Texture*> loadMaterialTextures(Model* model, aiMaterial* mat, aiTextureType type, string typeName, const string& path);

        ITextureFactory* _textureFactory;

        AbstractRender* render;

        std::map<string, shared_ptr<Model>> default_models;
        
    };
    
    
}

