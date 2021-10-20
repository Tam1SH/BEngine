#pragma once
#include "AbstractComponent.hpp"
#include <vulkan/vulkan.h>
#include "Vector3.h"
#include "matrix.hpp"
#include "VkBuffer.hpp"
#include "RenderBuffer.hpp"
namespace BEbraEngine {
    class TransformFactory;
    class Transform : public AbstractComponent {
    private:
        friend class TransformFactory;

        friend class RenderObjectFactory;

        static TransformFactory* factory;

        std::shared_ptr<RenderBuffer> buffer;


    private:
        Vector3 position;

        Vector3 scale;

        Vector3 rotation;

        Matrix4 model;
    private:

        static void SetFactory(TransformFactory* factory) noexcept;

        Transform(const Vector3& position);

    public:

        static Transform* New(const Vector3& position = Vector3(0));

        void UpdatePosition(const Vector3& position);

        void SetPosition(const Vector3& position) noexcept;

        void SetScale(const Vector3& scale) noexcept;

        Vector3 GetPosition() const noexcept;

        ~Transform() { };
    };
}