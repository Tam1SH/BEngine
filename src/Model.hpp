#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <vector>
#include <optional>
#include "Image.hpp"
#include "Vertex.hpp"
#include "RenderBuffer.hpp"
namespace BEbraEngine {
    class VulkanTextureFactory;
    class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Texture*> textures;
        RenderBufferView* vertices_view;
        RenderBufferView* indices_view;
        Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture*> textures)
            : vertices(vertices), indices(indices), textures(textures) {}
        Mesh() {}
        ~Mesh() {

        }
    };
    class Model
    {

    public:
        std::vector<Texture*> textures_loaded; 
        //TODO: вынести представление для каждого меша и использовать только одно.
        std::vector<Mesh> meshes;

        Model() {}
        ~Model() {
            for (auto& mesh : meshes) {
                mesh.vertices_view->buffer->destroy();
                mesh.indices_view->buffer->destroy();
                delete mesh.vertices_view;
                delete mesh.indices_view;
            }
        }
    };

}
