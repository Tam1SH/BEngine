#include <tbb.h>
#include <vulkan.h>
module VulkanTextureFactory;
import Logger;

namespace BEbraEngine {


    /*
    Task<optional<Material*>> VulkanTextureFactory::createMaterialAsync(const MaterialCreateInfo& info)
    {
        auto task = Task<optional<Material*>>();
        
        auto strColorLow = "";//((info.color.parent_path().string() / info.color.stem()).string() + "_low");
        auto strExensionColor = "";//info.color.extension().string();
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
    */

    Task<optional<Texture*>> VulkanTextureFactory::createAsync(const CreateTextureInfo& info)
    {
        auto& data = info.data;
        auto image = new VulkanTexture();
        Task<optional<Texture*>> task;

        image->setHeight(data.height);
        image->setWidth(data.width);      
        VkDeviceSize imageSize = 4;
        if (!(data.width == 0 || data.height == 0)) {
            imageSize = data.width * data.height * 4;
            image->setHeight(data.height);
            image->setWidth(data.width);
        }
        else {
            image->setHeight(1);
            image->setWidth(1);
        }

        const auto& generateMip = info.generateMip;

        // :)
        #define then [&]{
        #define еlse }():[&]{
        #define end }();

        generateMip? then
            const auto max = (((data.width) > (data.height)) ? (data.width) : (data.height));
            const auto log2 = std::log2(max);
            image->mipLevels = static_cast<uint32_t>(std::floor(log2)) + 1;
        еlse
            image->mipLevels = 1; 
            image->setLoaded();
        end

        tbb::task_arena{}.enqueue([=] {
            //смешно, но только из-за этого метода, этот же метод не является чистым)
            createVkTexture(info.data, image, imageSize);
            task.execute(std::make_optional(image), true);
        });

        return task;
    }

    optional<Texture*> VulkanTextureFactory::createEmpty()
    {
        auto image = new VulkanTexture();
        image->setHeight(1);
        image->setWidth(1);
        image->mipLevels = 1;
        image->setLoaded();
        createVkTexture({}, image, 4);
        return std::make_optional(image);
    }
  //  void VulkanTextureFactory::saveImage(const char* fileName, int width, int height, int channel_num, const void* rows, int quality) {
        //stbi_write_jpg(fileName, width, height, channel_num, rows, quality);
  //  }

  //  void VulkanTextureFactory::saveImage(const char* fileName, int width, int height, int channel_num, BEbraEngine::BitMap& bitMap, int quality)
  //  {
        /*
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
       */
  //  }
    //void VulkanTextureFactory::setDestroyer(VisitorGameComponentDestroyer& destroyer)
    //{
    //    this->destroyer = &destroyer;
    //}

    VulkanTextureFactory::VulkanTextureFactory(VulkanRender& render, TextureLoader& loader) 
        : render(&render), loader(&loader) { }

    void VulkanTextureFactory::createVkTexture(const TextureData& data, VulkanTexture* tex, size_t imageSize)
    {
        render->createVkImage(data.data, tex, imageSize);
        tex->imageView = render->createImageView(tex, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
        render->createTextureSampler(tex);
        loader->free(data);
    }

    void VulkanTextureFactory::destroyTextureAsync(shared_ptr<Texture> texture)
    {
        auto vTexture = std::static_pointer_cast<VulkanTexture>(texture);
        render->destroyTextureAsync(vTexture);
    }
}
