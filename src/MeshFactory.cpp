
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
module MeshFactory;
import RenderBufferView;
import CRenderAllocator;
import VulkanRenderAllocator;
import Model;
import Vector3;
import Vector2;
import <optional>;
import <fstream>;
import <variant>;

namespace BEbraEngine {

    namespace create {
        MeshFactory meshFactory(std::variant<VulkanRenderAllocator>& renderAlloc)
        {
            return MeshFactory(renderAlloc);
        }
    }

    std::optional<Model*> MeshFactory::create(const ModelCreateInfo& info)
    {

        auto model = new Model();
        auto name = info.path;
        if (name == "Box") {
            auto box = getDefaultModel("BOX");
            if (box.get())
                return std::optional<Model*>(&*box);
        }

        if (name == "Cylinder")
        {
            auto cylinder = getDefaultModel("Cylinder");
            if (cylinder.get())
                return std::optional<Model*>(&*cylinder);
        }

        if (name == "Sphere")
        {
            auto sphere = getDefaultModel("Sphere");
            if(sphere.get())
                return std::optional<Model*>(&*sphere);
        }
        // ������ ����� � ������� Assimp
        Assimp::Importer imposter;
        const aiScene* scene = imposter.ReadFile(info.path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        // �������� �� ������
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // ���� �� 0
        {
            //std::cout << "ERROR::ASSIMP:: " << imposter.GetErrorString() << std::endl;
            return std::make_optional<Model*>();
        }

        // ��������� ���� � �����
        //directory = path.substr(0, path.find_last_of('/'));
        // ����������� ��������� ��������� ���� Assimp
        processNode(model, scene->mRootNode, scene, info.path);
        auto model_out = std::make_optional<Model*>(model);
        return model_out;
    }

    std::optional<Model*> MeshFactory::createAsync(const ModelCreateInfo& info)
    {
        return std::optional<Model*>();
    }
    std::shared_ptr<Model> MeshFactory::getDefaultModel(const std::string& name)
    {
        return default_models[name];
    }

    MeshFactory::MeshFactory(std::variant<VulkanRenderAllocator>& renderAlloc)
        : renderAlloc(&renderAlloc) 
    {

        downloadDefaultModels(); 
    }

    void MeshFactory::downloadDefaultModels()
    {
        std::visit([&](CRenderAllocator auto& renderAlloc) {

            
            const char* box = "BOX";
            const char* sphere = "SPHERE";
            const char* cylinder = "CYLINDER";

            ModelCreateInfo info{};

            //info.path = boost::filesystem::current_path() / "Models/Box.fbx";;
            default_models[box] = std::shared_ptr<Model>(create(info).value());
            auto vertices_view = new RenderBufferView();
            vertices_view->buffer = std::shared_ptr<RenderBuffer>(renderAlloc.createVertexBuffer(default_models[box]->meshes[0].vertices));
            default_models[box]->meshes[0].vertices_view = vertices_view;
            auto indices_view = new RenderBufferView();
            indices_view->buffer = std::shared_ptr<RenderBuffer>(renderAlloc.createIndexBuffer(default_models[box]->meshes[0].indices));
            default_models[box]->meshes[0].indices_view = indices_view;


           // info.path = boost::filesystem::current_path() / "Models/Sphere.fbx";;
            default_models[sphere] = std::shared_ptr<Model>(create(info).value());
            vertices_view = new RenderBufferView();
            vertices_view->buffer = std::shared_ptr<RenderBuffer>(renderAlloc.createVertexBuffer(default_models[sphere]->meshes[0].vertices));
            default_models[sphere]->meshes[0].vertices_view = vertices_view;
            indices_view = new RenderBufferView();
            indices_view->buffer = std::shared_ptr<RenderBuffer>(renderAlloc.createIndexBuffer(default_models[sphere]->meshes[0].indices));
            default_models[sphere]->meshes[0].indices_view = indices_view;

           // info.path = boost::filesystem::current_path() / "Models/Cylinder.fbx";;
            default_models[cylinder] = std::shared_ptr<Model>(create(info).value());
            vertices_view = new RenderBufferView();
            vertices_view->buffer = std::shared_ptr<RenderBuffer>(renderAlloc.createVertexBuffer(default_models[cylinder]->meshes[0].vertices));
            default_models[cylinder]->meshes[0].vertices_view = vertices_view;
            indices_view = new RenderBufferView();
            indices_view->buffer = std::shared_ptr<RenderBuffer>(renderAlloc.createIndexBuffer(default_models[cylinder]->meshes[0].indices));
            default_models[cylinder]->meshes[0].indices_view = indices_view;

        }, *renderAlloc);
    }

    void MeshFactory::processNode(Model* model, aiNode* node, const aiScene* scene, const std::string& path)
    {
        // ������������ ������ ��� �������� ����
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // ���� �������� ������ ������� �������� � �����.
            // ����� �� �������� ��� ������; ���� - ��� ���� ������ ����������� ������
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            model->meshes.push_back(processMesh(model, mesh, scene, path));
        }
        // ����� ����, ��� �� ���������� ��� ���� (���� ������� �������), �� �������� ���������� ������������ ������ �� �������� �����
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(model, node->mChildren[i], scene, path);
        }

    }
    Mesh MeshFactory::processMesh(Model* model, aiMesh* mesh, const aiScene* scene, const std::string& path)

    {
        // ������ ��� ����������
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Texture*> textures;

        // ���� �� ���� �������� ����
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            Vector3 vector; // �� ��������� ������������� ������, �.�. Assimp ���������� ���� ����������� ��������� �����, ������� �� ������������� �������� � ��� glm::vec3, ������� ������� �� �������� ������ � ���� ������������� ������ ���� glm::vec3

            // ����������
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector.toVec<UnbelivableVector3FromMSVC>();

            // �������
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector.toVec<UnbelivableVector3FromMSVC>();

            // ���������� ����������
            if (mesh->mTextureCoords[0]) // ���� ��� �������� ���������� ����������
            {
                Vector2 vec;

                // ������� ����� ��������� �� 8 ��������� ���������� ���������. �� ������������, ��� �� �� ����� ������������ ������,
                // � ������� ������� ����� ��������� ��������� ���������� ���������, ������� �� ������ ����� ������ ����� (0)
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoord = vec;
            }
            else
                vertex.texCoord = Vector2(0.0f, 0.0f);

            // ����������� ������
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            // vertex.Tangent = vector;

             // ������ ���������
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            //  vertex.Bitangent = vector;
            vertices.push_back(vertex);
        }
        // ������ ���������� �� ������ ����� ���� (����� - ��� ����������� ����) � ��������� ��������������� ������� ������
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            // �������� ��� ������� ������ � ��������� �� � ������� indices
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // ������������ ���������
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];


        std::vector<Texture*> diffuseMaps = loadMaterialTextures(model, material, aiTextureType_DIFFUSE, "texture_diffuse", path);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());


        std::vector<Texture*> specularMaps = loadMaterialTextures(model, material, aiTextureType_SPECULAR, "texture_specular", path);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());


        std::vector<Texture*> normalMaps = loadMaterialTextures(model, material, aiTextureType_HEIGHT, "texture_normal", path);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());


        std::vector<Texture*> heightMaps = loadMaterialTextures(model, material, aiTextureType_AMBIENT, "texture_height", path);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        auto _mesh = Mesh(vertices, indices, textures);
        auto indices_view = new RenderBufferView();
        auto vertices_view = new RenderBufferView();

        std::visit([&](CRenderAllocator auto& renderAlloc) {
            indices_view->buffer = std::shared_ptr<RenderBuffer>(renderAlloc.createIndexBuffer(_mesh.indices));
            vertices_view->buffer = std::shared_ptr<RenderBuffer>(renderAlloc.createVertexBuffer(_mesh.vertices));
            _mesh.indices_view = indices_view;
            _mesh.vertices_view = vertices_view;

        }, *renderAlloc);


        return _mesh;
    }
    std::vector<Texture*> MeshFactory::loadMaterialTextures(Model* model, aiMaterial* mat, aiTextureType type, std::string typeName, const std::string& path)

    {
        std::vector<Texture*> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            // ���������, �� ���� �� �������� ��������� �����, � ���� - ��, �� ���������� �������� ����� �������� � ��������� � ��������� ��������
            bool skip = false;
            for (unsigned int j = 0; j < model->textures_loaded.size(); j++)
            {
                if (std::strcmp(path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(model->textures_loaded[j]);
                    skip = true; // �������� � ��� �� ����� � ����� ��� ���������, ��������� � ��������� (�����������)
                    break;
                }
            }
            if (!skip)
            {   // ���� �������� ��� �� ���� ���������, �� ��������� �
                Texture* texture;
                //texture = _textureFactory->create(path);
                textures.push_back(texture);
                model->textures_loaded.push_back(texture); // ��������� �������� � ������� � ��� ������������ ����������, ��� ����� ����������, ��� � ��� �� �������� ��� ������������� ��������� �������
            }
        }
        return textures;
    }

    
    
}