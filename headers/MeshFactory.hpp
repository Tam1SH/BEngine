#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "Model.hpp"

using BE_STD::optional;
using BE_STD::shared_ptr;
using BE_STD::string;
using BE_STD::map;
using BE_STD::vector;

namespace BEbraEngine {
    class AbstractRender;
    class ITextureFactory;
}
namespace BEbraEngine {

    class MeshFactory {
    public:

        optional<Model*> create(const Model::ModelCreateInfo& info);

        optional<Model*> createAsync(const Model::ModelCreateInfo& info);

        shared_ptr<Model> getDefaultModel(const string& name);

        MeshFactory(AbstractRender* render);
    private:


        void downloadDefaultModels();
        // –екурсивна€ обработка узла. ќбрабатываем каждый отдельный меш, расположенный в узле, и повтор€ем этот процесс дл€ своих дочерних углов (если таковы вообще имеютс€)
        void processNode(Model* model, aiNode* node, const aiScene* scene, const string& path);

        Mesh processMesh(Model* model, aiMesh* mesh, const aiScene* scene, const string& path);

        // ѕровер€ем все текстуры материалов заданного типа и загружам текстуры, если они еще не были загружены.
        // Ќеобходима€ информаци€ возвращаетс€ в виде структуры Texture
       vector<Texture*> loadMaterialTextures(Model* model, aiMaterial* mat, aiTextureType type, string typeName, const string& path);

       ITextureFactory* _textureFactory;

       AbstractRender* render;

       map<string, shared_ptr<Model>> default_models;

    };
}

