#pragma once
#include "stdafx.h"
#include "Model.hpp"
template<typename T>
class std::shared_ptr;
namespace BEbraEngine {
    class AbstractRender;
}
namespace BEbraEngine {
    class MeshFactory {
    public:

        std::optional<Model*> create(const std::string& path);
        std::shared_ptr<Model> getDefaultModel(const std::string& name);
        MeshFactory(std::shared_ptr<AbstractRender> render);
    private:

        void downloadDefaultModels();
        // –екурсивна€ обработка узла. ќбрабатываем каждый отдельный меш, расположенный в узле, и повтор€ем этот процесс дл€ своих дочерних углов (если таковы вообще имеютс€)
        void processNode(Model* model, aiNode* node, const aiScene* scene, const std::string& path);

        Mesh processMesh(Model* model, aiMesh* mesh, const aiScene* scene, const std::string& path);

        // ѕровер€ем все текстуры материалов заданного типа и загружам текстуры, если они еще не были загружены.
        // Ќеобходима€ информаци€ возвращаетс€ в виде структуры Texture
        std::vector<Texture*> loadMaterialTextures(Model* model, aiMaterial* mat, aiTextureType type, std::string typeName, const std::string& path);

        TextureFactory* _textureFactory;

        std::shared_ptr<AbstractRender> render;

        std::map<std::string, std::shared_ptr<Model>> default_models;

    };
}

