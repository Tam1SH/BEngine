#pragma once
#include "stdafx.h"

#include "Model.hpp"
#include "IRenderObjectFactory.hpp"
namespace BEbraEngine {
    class VulkanBuffer;
    class AbstractRender;
    class VulkanRender;
    class Texture;
    class VulkanTextureFactory;
    class RenderObject;
    class VulkanRenderObject;
    class RenderObjectInfo;
    class VulkanRenderBufferPool;
    class MeshFactory;
    class Transform;
    class Camera;
}
namespace std {
    template<typename T>
    class shared_ptr;
    template<typename T, class D>
    class unique_ptr;
    template<typename T>
    class weak_ptr;


}
namespace BEbraEngine {

    class VulkanRenderObjectFactory : public IRenderObjectFactory
    {
    public:

        void bindTransform(std::shared_ptr<PointLight> light, std::shared_ptr<Transform> transform) override;

        void bindTransform(std::shared_ptr<RenderObject> object, std::shared_ptr<Transform> transform) override;

        void setTexture(RenderObject* object, const boost::filesystem::path& path) override;

        void setTexture(RenderObject* object, Texture const* path) override;

        std::optional<RenderObject*> createObject() override;

        PointLight* createLight(const Vector3& color, const Vector3& position) override;

        DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) override;

        Camera* createCamera(const Vector3& position) override;

        void setContext(AbstractRender* render) override;
       
        void destroyObject(std::shared_ptr<RenderObject> object) override;

        void destroyPointLight(std::shared_ptr<PointLight> light) override;

        void destroyCamera(std::shared_ptr<Camera> camera) override;

        void setModel(RenderObject* object, const std::string& path) override;

        void CreateObjectSet(VulkanRenderObject* obj);

        VulkanRenderObjectFactory();
        ~VulkanRenderObjectFactory();

        void SetImgsCreator(VulkanTextureFactory* Creator) { textureFactory = Creator; }
    private:
        std::unique_ptr<VulkanRenderBufferPool> _poolofObjects;
        std::unique_ptr<VulkanRenderBufferPool> _poolofPointLights;
        std::unique_ptr<VulkanRenderBufferPool> _poolofDirLights;

        std::shared_ptr<RenderBufferView> storage;

        VkDescriptorSet set;

        VulkanRender* render;
        VulkanTextureFactory* textureFactory;
        std::unique_ptr<MeshFactory> meshFactory;

    };
}

/*
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
using namespace std;

struct Vertex {

    // �������
    glm::vec3 Position;

    // �������
    glm::vec3 Normal;

    // ���������� ����������
    glm::vec2 TexCoords;

    // ����������� ������
    glm::vec3 Tangent;

    // ������ ��������� (������, ���������������� ������������ ������� � ������� �������)
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // ������ ����
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    // �����������
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        // ������, ����� � ��� ���� ��� ����������� ������, ������������� ��������� ������ � ��������� ���������
        setupMesh();
    }

    // ��������� ����
    void Draw()
    {
        // ��������� ��������������� ��������
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // ����� ����������� ���������� ������ ���������� ����

            // �������� ����� �������� (����� N � diffuse_textureN)
            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // ������������ unsigned int � ������
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // ������������ unsigned int � ������
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // ������������ unsigned int � ������

            // ������ ������������� ������� �� ������ ���������� ����
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            // � ��������� ��������
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        // ������������ ���
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // ��������� ������� ��������� ���������� �������� ���������� � �� �������������� ���������
        glActiveTexture(GL_TEXTURE0);
    }

private:
    // ������ ��� ���������� 
    unsigned int VBO, EBO;

    // �������������� ��� �������� �������/�������
    void setupMesh()
    {
        // ������� �������� �������/�������
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // ��������� ������ � ��������� �����
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // ����� ������������� � ���������� ��, ��� ������������ � ������ �� ���������� ���������� �������� ����������������.
        // ����� ������� ����� � ���, ��� �� ����� ������ �������� ��������� �� ���������, � ��� ��������� ������������� � ������ ������ � ���������� ���� glm::vec3 (��� glm::vec2), ������� ����� ����� ������������ � ������ ������ float, �� � � ����� � � �������� ������
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // ������������� ��������� ��������� ���������

        // ���������� ������
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // ������� ������
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        // ���������� ���������� ������
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        // ����������� ������ �������
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

        // ������ ��������� �������
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

        glBindVertexArray(0);
    }
};
*/