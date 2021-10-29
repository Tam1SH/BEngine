#pragma once
/*
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <vector>

#include "Image.hpp"
#include "Vertex.h"
namespace BEbraEngine {
    class ImageCreator;

    class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Texture*> textures;
        Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture*> textures)
            : vertices(vertices), indices(indices), textures(textures) {}
        Mesh() {}
    };
    class Model
    {
    private:
        static ImageCreator* creator;

    public:
        static void SetCreator(ImageCreator* creator) {
            Model::creator = creator;
        }
        static Model* New();
        // ƒанные модели 
        std::vector<Texture*> textures_loaded; // (оптимизаци€) сохран€ем все загруженные текстуры, чтобы убедитьс€, что они не загружены более одного раза
        std::vector<Mesh> meshes;
        std::string path;
        bool gammaCorrection;

        //  онструктор в качестве аргумента использует путь к 3D-модели
        Model(std::string const& path, bool gamma = false);

        // ќтрисовываем модель, а значит и все еЄ меши
        void Draw();

    private:
        // «агружаем модель с помощью Assimp и сохран€ем полученные меши в векторе meshes
        void loadModel(std::string const& path);

        // –екурсивна€ обработка узла. ќбрабатываем каждый отдельный меш, расположенный в узле, и повтор€ем этот процесс дл€ своих дочерних углов (если таковы вообще имеютс€)
        void processNode(aiNode* node, const aiScene* scene);

        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        // ѕровер€ем все текстуры материалов заданного типа и загружам текстуры, если они еще не были загружены.
        // Ќеобходима€ информаци€ возвращаетс€ в виде структуры Texture
        std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    };

}
*/