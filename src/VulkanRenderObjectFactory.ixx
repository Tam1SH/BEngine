

#include "platform.hpp"
#include <boost/filesystem.hpp>
#include <tbb.h>
#include <variant>


export module VulkanRenderObjectFactory;
import Light;
import Camera;
import RenderObject;
/*Objects*/

import Material;
import DirectionLight;
import Texture;
import Transform;
/*Objects*/
import VulkanTextureFactory;
import MeshFactory;
import RenderBuffer;
import VulkanRenderBufferArray;
import VulkanRender;
import VulkanRenderAllocator;
import RenderBufferArray;
import CRenderAllocator;
import CRender;
import Task;
import Model;



import <memory>;
import <string>;
import <optional>;
//разделить логику и создание/удаление(назв. Adjuster?) также для рендера создать чтоли стораге?
using std::shared_ptr;
using std::unique_ptr;
using std::optional;
using std::string;


namespace BEbraEngine {
    
    export class VulkanRenderObjectFactory
    {
    public:
        Task<optional<Material*>> createMaterialAsync(shared_ptr<RenderObject> obj, const MaterialCreateInfo& info);

        optional<RenderObject*> create(const RenderObjectCreateInfo& info);

        void setMaterial(RenderObject& obj, Material& material);

       // void setComponentDestroyer(VisitorGameComponentDestroyer& destroyer);

        void bindTransform(Light& light, Transform& transform);

        void bindTransform(RenderObject& object, Transform& transform);

        Light* createLight(const Vector3& color, const Vector3& position);

        DirectionLight* createDirLight(const Vector3& color, const Vector3& direction);

        SimpleCamera* createCamera(const Vector3& position);
       
        void destroyObject(RenderObject& object);

        void destroyPointLight(Light& light);

        void destroyCamera(SimpleCamera& camera);

        void setModel(RenderObject& object, const string& path);

        
        VulkanRenderObjectFactory(VulkanRender& render, VulkanRenderAllocator& allocator);

        VulkanRenderObjectFactory() {}
        ~VulkanRenderObjectFactory();

        VulkanRenderObjectFactory(VulkanRenderObjectFactory&&) noexcept = default;
        VulkanRenderObjectFactory& operator=(VulkanRenderObjectFactory&&) noexcept = default;
        VulkanRenderObjectFactory(const VulkanRenderObjectFactory&) noexcept = delete;
        VulkanRenderObjectFactory& operator=(const VulkanRenderObjectFactory&) noexcept = delete;



    private:
        unique_ptr<VulkanRenderBufferArray<RenderObject::ShaderData>> _poolofObjects;
        unique_ptr<VulkanRenderBufferArray<Light::ShaderData>> _poolofPointLights;
        unique_ptr<VulkanRenderBufferArray<DirectionLight::ShaderData>> _poolofDirLights;

        shared_ptr<RenderBufferView> storage;
        //VisitorGameComponentDestroyer* destroyer;
        VulkanRender* render;
        VulkanRenderAllocator* allocator;
        VulkanTextureFactory* textureFactory;
        unique_ptr<MeshFactory> meshFactory;
        
    };

    namespace create {

        export std::variant<VulkanRenderObjectFactory> renderObjectFactory(CRender auto& render, CRenderAllocator auto& allocator) {
            static_assert("no implementation found, check type");
        }

        export template<> std::variant<VulkanRenderObjectFactory> renderObjectFactory(VulkanRender& render, VulkanRenderAllocator& allocator);
    }
}


module :private;
import CRenderObjectFactory;
namespace BEbraEngine {
    static_assert(CRenderObjectFactory<VulkanRenderObjectFactory>);
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