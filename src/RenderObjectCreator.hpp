#pragma once
#include "Image.hpp"
#include "ImageCreator.hpp"
#include "Transform.hpp"
#include <mutex>
#include <iostream>
#include <vector>
#include "Model.h"
namespace BEbraEngine {
    class VkObject;
    class RenderObject;
    class VulkanRender;
    class RenderObjectFactory
    {
    public:

        friend class RenderObject;


        VulkanRender* render;
        ImageCreator* imgsCreator;

        std::mutex m;
    private:

        template<typename T>
        Buffer CreateBuffer(std::vector<T>& data, VkBufferUsageFlags usage, VkCommandBuffer& cmdBuffer);

        template<typename T>
        Buffer CreateBuffer(std::vector<T>& data, VkBufferUsageFlags usage);

        Texture CreateImage(Texture img);

        Buffer CreateIndexBuffer(std::vector<uint32_t> indices, VkCommandBuffer& cmdBuffer);

        Buffer CreateVertexBuffer(std::vector<Vertex> vertices, VkCommandBuffer& cmdBuffer);

        Buffer CreateIndexBuffer(std::vector<uint32_t> indices);

        Buffer CreateVertexBuffer(std::vector<Vertex> vertices);


        void CreateSet(Buffer& uniformBuffer, VkDeviceSize size, Texture* texture, VkDescriptorSet& set);
    public:
        friend class Transform;

        RenderObject* CreateObject(std::shared_ptr<Transform> transform);

        void CreateObjectSet(RenderObject* obj);

        Buffer* CreateUniformBuffer(VkDeviceSize size);

        void CreateStorageBuffer(VkDeviceSize size, Buffer& buffer);

        RenderObjectFactory(VulkanRender* render);

        RenderObjectFactory() {}

        void SetRender(VulkanRender* render) { this->render = render; }

        void SetImgsCreator(ImageCreator* Creator) { imgsCreator = Creator; }


        void Update(RenderObject* obj);

     //   Model* CreateModel(std::string const& path) {
      //      return new Model(path);
      //  }
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