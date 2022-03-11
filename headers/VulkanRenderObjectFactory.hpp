#pragma once
#include "stdafx.h"
#include "platform.hpp"
#include "Model.hpp"
#include "IRenderObjectFactory.hpp"

using BE_STD::shared_ptr;
using BE_STD::unique_ptr;
using BE_STD::optional;
using BE_STD::string;

BE_NAMESPACE_STD_BEGIN
template<typename T>
class shared_ptr;
template<typename T, class D>
class unique_ptr;
template<typename T>
class weak_ptr;

BE_NAMESPACE_STD_END



namespace BEbraEngine {

    class VulkanBuffer;
    class AbstractRender;
    class VulkanRender;
    class Texture;
    class VulkanTextureFactory;
    class RenderObject;
    class VulkanRenderObject;
    class RenderObjectInfo;
    class MeshFactory;
    class Transform;
    class DirectionLight;
    class SimpleCamera;
    class Light;
    template<typename RenderData>
    class VulkanRenderBufferPool;
}


namespace BEbraEngine {

    class VulkanRenderObjectFactory : public IRenderObjectFactory
    {
    public:
        friend class VulkanRender;

        ITextureFactory& getTextureFactory() override;

        void bindTransform(Light& light, Transform& transform) override;

        void bindTransform(RenderObject& object, Transform& transform) override;

        void setTexture(RenderObject& object, const boost::filesystem::path& path) override;

        void setTexture(shared_ptr<RenderObject>  object, Texture const& path) override;

        optional<RenderObject*> create(const RenderObject::RenderObjectCreateInfo& info) override;

        Light* createLight(const Vector3& color, const Vector3& position) override;

        DirectionLight* createDirLight(const Vector3& color, const Vector3& direction) override;

        SimpleCamera* createCamera(const Vector3& position) override;

        void setContext(AbstractRender* render) override;
       
        void destroyObject(RenderObject& object) override;

        void destroyPointLight(Light& light) override;

        void destroyCamera(SimpleCamera& camera) override;

        void setModel(RenderObject& object, const string& path) override;

        void CreateObjectSet(VulkanRenderObject* obj);

        VulkanRenderObjectFactory();
        ~VulkanRenderObjectFactory();

    private:
        unique_ptr<VulkanRenderBufferPool<RenderObject::ShaderData>> _poolofObjects;
        unique_ptr<VulkanRenderBufferPool<Light::ShaderData>> _poolofPointLights;
        unique_ptr<VulkanRenderBufferPool<DirectionLight::ShaderData>> _poolofDirLights;

        shared_ptr<RenderBufferView> storage;

        VulkanRender* render;
        VulkanTextureFactory* textureFactory;
        unique_ptr<MeshFactory> meshFactory;

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