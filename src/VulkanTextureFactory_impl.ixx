
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <variant>
#include <stb-master/stb_image.h>
#include <stb-master/stb_image_write.h>
#include <boost/filesystem.hpp>
#include <tbb.h>
#include <vulkan.h>
#include <cmath>
#include <algorithm>

export module VulkanTextureFactory_impl;
import VulkanTextureFactory;
import VulkanRender;
import Task;
import Render;
import Material;
import <optional>;
import <vector>;
import <memory>;
using std::function;
using std::optional;
using std::vector;
using std::shared_ptr;
namespace BEbraEngine {
    namespace create {
    }
    Task<optional<Material*>> VulkanTextureFactory::createMaterialAsync(const MaterialCreateInfo& info)
    {
        auto task = Task<optional<Material*>>();

        auto strColorLow = ((info.color.parent_path().string() / info.color.stem()).string() + "_low");
        auto strExensionColor = info.color.extension().string();
        auto image = std::shared_ptr<Texture>(create(strColorLow + strExensionColor, false));

        
        tbb::task_arena g;

        g.enqueue([=]() {
            auto strColor = ((info.color.parent_path().string() / info.color.stem()).string());
            auto strSpecular = ((info.specular.parent_path().string() / info.specular.stem()).string());
            auto strNormal = ((info.normal.parent_path().string() / info.normal.stem()).string());

            auto strExensionColor = info.color.extension().string();
            auto strExensionSpecular = info.specular.extension().string();
            auto strExensionNormal = info.normal.extension().string();

            auto color = create(strColor + strExensionColor, true);

            auto specular = create(strSpecular + strExensionSpecular, false);
            auto normal = create(strNormal + strExensionNormal, false);

            task.execute(new Material(color, specular, normal), true);

        });

        return task;

    }

    Task<optional<Texture*>> VulkanTextureFactory::createAsync(const boost::filesystem::path& path)
    {
        auto task = Task<optional<Texture*>>();
        auto str = ((path.parent_path().string() / path.stem()).string() + "_low");
        auto str1 = path.extension().string();
        auto path_low = str + str1;
        auto image = create(path_low, false);

        tbb::task_arena g;
        g.enqueue([=]() {
            auto str = ((path.parent_path().string() / path.stem()).string());
            auto str1 = path.extension().string();

            std::string path = str + str1;
            Texture* image = create(path, true);
            
            task.execute(image, true);
        });

        return task;

    }
    Texture* VulkanTextureFactory::create(const boost::filesystem::path& path, bool generateMip)
    {
        
        VulkanTexture* image = new VulkanTexture();
        int texWidth, texHeight, texChannels;
       // stbi_set_flip_vertically_on_load(true);
        
        stbi_uc* rows = stbi_load(path.string().c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        image->setHeight(texHeight);
        image->setWidth(texWidth);
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        if (!rows)
        {
            //if(!path.string().empty())
                //DEBUG_LOG2("failed to upload texture. uncorrect path or file don't exist. | path: " + path.string(),
                //    image, "", Debug::ObjectType::Empty, Debug::MessageType::Error);
            rows = new unsigned char[4];
            rows[0] = 255;
            rows[1] = 255;
            rows[2] = 255;
            texWidth = 1, texHeight = 1;
            imageSize = 4 * texWidth * texHeight;
            image->setHeight(texHeight);
            image->setWidth(texWidth);
        }

        if (generateMip) {
            //auto max = std::max(texWidth, texHeight);
            //auto log2 = std::log2(max);
            //image->mipLevels = static_cast<uint32_t>(std::floor(log2)) + 1;
        }
         else {

            image->mipLevels = 1;
            image->setLoaded();
        }

        render->createVkImage(rows, image, imageSize);
        image->imageView = render->createImageView(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
        stbi_image_free(rows);
        
        render->createTextureSampler(image);
        return image;

    }
    Texture* VulkanTextureFactory::createEmpty()
    {
        return create("", false);
    }
    void VulkanTextureFactory::saveImage(const char* fileName, int width, int height, int channel_num, const void* rows, int quality) {
        stbi_write_jpg(fileName, width, height, channel_num, rows, quality);
    }

    void VulkanTextureFactory::saveImage(const char* fileName, int width, int height, int channel_num, BEbraEngine::BitMap& bitMap, int quality)
    {
        
        tbb::task_arena t;
        auto pBitMap = &bitMap;
        //t.enqueue([=]() {
            //DEBUG_LOG1("BEGIN TASK");
            vector<uint8_t> pixelsConvert;
            pixelsConvert.resize(width * height * channel_num);
            int index{};
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                   
                    pixelsConvert[index++] = pBitMap->at(y)[x].x;
                    pixelsConvert[index++] = pBitMap->at(y)[x].y;
                    pixelsConvert[index++] = pBitMap->at(y)[x].z;
                }
            }
            stbi_write_jpg(fileName, width, height, channel_num, pixelsConvert.data(), quality);
        //});
       
    }
    //void VulkanTextureFactory::setDestroyer(VisitorGameComponentDestroyer& destroyer)
    //{
    //    this->destroyer = &destroyer;
    //}

    VulkanTextureFactory::VulkanTextureFactory(VulkanRender& render) 
        : render(&render) { }

    void VulkanTextureFactory::destroyTexture(Texture& texture)
    {
        throw std::exception();
    }
    void VulkanTextureFactory::destroyTextureAsync(shared_ptr<Texture> texture)
    {
        auto vTexture = std::static_pointer_cast<VulkanTexture>(texture);
        render->destroyTextureAsync(vTexture);
    }
}
